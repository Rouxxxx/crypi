#include <iostream>
#include <string>
#include <vector>

#include "BFV/bfv.hh"
#include "seal/seal.h"
#include "utils/utils.hh"
#include "tests/Tester.hh"
#include "webserver/webserver.hh"

using namespace seal;

void handle_args(int argc, char **argv, Container* container)
{
    for (int id = 1; id < argc; id++) {
        std::string cur_arg = argv[id];
        if (cur_arg == "--check") {
            Tester test(std::cout, container->infos_struct);
            exit(0);
        }

        else if (cur_arg == "--skip-social-verif")
            container->infos_struct.skip_social_verif = true;
    }
}

int main(int argc, char** argv)
{
    Infos infos_obj;

    // Load infos from JSON
    infos_obj.build_static_info("src/config.json");

    Container container(infos_obj);

    // Pretty Print
    container.print_parameters();

    // Check if we run tests
    handle_args(argc, argv, &container);

    // Init BGV keys
    container.init_public_key();
    container.init_secret_key();

    std::vector<Candidate> candidates = get_candidates("data/candidates.txt", 30);

    return Wt::WRun(argc, argv, [&container, candidates](const Wt::WEnvironment& env) {
        return std::make_unique<EvoteApplication>(env, &container, candidates);
    });
}
