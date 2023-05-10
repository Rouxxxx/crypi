#include "BFV_tests.hh"
#include <string>

bool Tester::basic_test()
{
    return 1;
}

void print_vector(std::vector<uint64_t> vec, int size)
{
    int s = vec.size();
    if (s == 0)
        return;

    std::cout << vec[0];
    for (int i = 1; i < size && i < s; i++)
        std::cout << " " << vec[i];

    std::cout << std::endl;
}





/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#            Simple example
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/

bool simple_example(Container* container)
{
    // Test of the save / import feature
    container->save_secret();
    container->load_secret();

    // Init two values and encrypt them
    uint64_t x = 6;
    std::string x1 = uint64_to_hex_string(x);
    Ciphertext x_encrypted = container->encrypt(x1);

    uint64_t y = 40;
    std::string y1 = uint64_to_hex_string(y);
    Ciphertext y_encrypted = container->encrypt(y1);

    // Compute the sum / multiplication
    Ciphertext sum = container->sum(x_encrypted, y_encrypted);
    Plaintext sum_decrypted = container->decrypt(sum);

    Ciphertext mult = container->multiply(x_encrypted, y_encrypted);
    Plaintext mult_decrypted = container->decrypt(mult);

    uint64_t s = x + y;
    uint64_t m = x * y;

    std::string hex_s = uint64_to_hex_string(s);
    std::string hex_m = uint64_to_hex_string(m);
 
    std::string hex_s_dec = sum_decrypted.to_string();
    std::string hex_m_dec = mult_decrypted.to_string();

    // Print to see if everything's right
    std::cout << "x:" << x1 << ", y:" << y1 << "\n";
    std::cout << "addition: " << hex_s
              << ", decrypted addition: " << hex_s_dec << "\n";
    std::cout << "multiplication: " << hex_m
              << ", decrypted multiplication: " << hex_m_dec
              << "\n";

    return (hex_s == hex_s_dec && hex_m == hex_m_dec);
}

bool Tester::simple_test()
{
    Container container(infos);
    container.init_public_key();
    container.init_secret_key();
    return simple_example(&container);
}





/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#            Real life example
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/

std::vector<uint64_t> generate_random_vector(int n)
{
    std::vector<uint64_t> vote(n, 0);
    // Set a random position in the vector to 1
    uint64_t rand_pos = rand() % n;
    vote[rand_pos] = 1;
    return vote;
}

// Simulate a list of votes
// Loop and generate n random votes for x candidates
// We keep track of the list of votes in a vector, so we can check if the result
// is accurate
bool vote_example(Container* container, int nb_candidates, int nb_votes)
{
    // Seed so the random is efficient
    srand(time(NULL));

    // Create all useful vars
    std::vector<std::vector<uint64_t>> votes(nb_votes);
    Ciphertext cipher;
    Ciphertext nb_votes_cipher;

    // Compute random votes, and add them to the Ciphertext
    for (int i = 0; i < nb_votes; i++)
    {
        // Encrypt then encode the vector (vector -> plaintext -> encrypted
        // plaintext)
        votes[i] = generate_random_vector(nb_candidates);
        Plaintext txt = container->encode_vector(votes[i]);
        Ciphertext tmp_cipher = container->encrypt(txt);

        // Encode the nb which will be added to the counter
        Ciphertext tmp_nb_votes = encrypt_number(container, 1);

        // Homomorphic addition
        // Add the vector AND the nb of votes
        if (i == 0)
        {
            cipher = tmp_cipher;
            nb_votes_cipher = tmp_nb_votes;
        }
        else
        {
            cipher = container->sum(cipher, tmp_cipher);
            nb_votes_cipher = container->sum(nb_votes_cipher, tmp_nb_votes);
        }
    }

    // Decrypt the number of votes
    Plaintext nb_votes_decrypted = container->decrypt(nb_votes_cipher);

    // Decrypt then decode the vector (encrypted plaintext -> decrypted
    // plaintext -> vector)
    Plaintext decrypted = container->decrypt(cipher);
    std::vector<uint64_t> result = container->decode_vector(decrypted);

    // Printing results
    int nb_votes_decrypted_int = hex_to_int(nb_votes_decrypted.to_string());
    std::cout << "Nb votes decrypted: " << nb_votes_decrypted_int
              << std::endl;

    if (nb_votes_decrypted_int != nb_votes) {
        std::cout << "ERROR: vote numbers don't match (actual number: " << nb_votes << ")";
        return false;
    }
    else
        std::cout << "Nb votes is good !\n";

    std::cout << "\nVotes:\n";

    // Create a vector to check if the operations are accurate.
    std::vector<uint64_t> checker(nb_candidates, 0);
    for (int i = 0; i < nb_votes; i++)
        for (int j = 0; j < nb_candidates; j++)
            checker[j] += votes[i][j];

    std::cout << "Real vote result:\n";
    print_vector(checker, nb_candidates);

    std::cout << "Result computed:\n";
    print_vector(result, nb_candidates);

    bool ok = true;
    for (int id = 0; id < nb_candidates; id++)
    {
        if (checker[id] != result[id])
        {
            ok = false;
            break;
        }
    }

    (ok) ? std::cout << "Vectors match\n"
         : std::cout << "ERROR : Vectors don't match\n";
    return ok;
}

bool Tester::real_life_test()
{
    Container container(infos);
    container.init_public_key();
    container.init_secret_key();

    return vote_example(&container, 6, 10000);
}


