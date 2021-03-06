#ifndef POAC_SUBCMD_LOGIN_HPP
#define POAC_SUBCMD_LOGIN_HPP

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdlib>

#include <boost/filesystem.hpp>

#include "../core/except.hpp"
#include "../io/cli.hpp"
#include "../io/path.hpp"
#include "../io/tar.hpp"
#include "../io/yaml.hpp"
#include "../util/termcolor2.hpp"


namespace poac::subcmd {
    namespace _login {
        template<typename VS>
        int _main(VS&& argv) {
            namespace fs     = boost::filesystem;
            namespace except = core::except;

            if (fs::create_directories(io::path::poac_state_dir)) {
                throw except::invalid_second_arg("login");
            }

            const std::string token_path = io::path::poac_token_dir.string();
            if (std::ofstream ofs(token_path); ofs) {
                ofs << argv[0] << std::endl;
                std::cout << termcolor2::bold<>
                          << "Write to " + token_path
                          << termcolor2::reset<>
                          << std::endl;
            }
            else { // file open error
                throw except::invalid_second_arg("login");
            }
            return EXIT_SUCCESS;
        }

        void check_arguments(const std::vector<std::string> &argv) {
            namespace except = core::except;
            if (argv.size() != 1) {
                throw except::invalid_second_arg("login");
            }
        }
    }

    struct login {
        static std::string summary() { return "Login to poac.pm"; }
        static std::string options() { return "<token>"; }
        template <typename VS>
        int operator()(VS&& argv) {
            _login::check_arguments(argv);
            return _login::_main(std::forward<VS>(argv));
        }
    };
} // end namespace
#endif // !POAC_SUBCMD_LOGIN_HPP
