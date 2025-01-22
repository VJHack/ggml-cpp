
#include "common.h"

// Function to check if the next argument exists
static std::string get_next_arg(int& i, int argc, char** argv, const std::string& flag, gpt_params& params){
    if(i + 1 < argc && argv[i + 1][0] != '-') {
        return argv[++i];
    } else {
        fprintf(stderr, "Error: %s requires an argument.\n", flag.c_str());
        exit(0);
    }
}

bool gpt_params_parse(int argc, char ** argv, gpt_params & params){
    for(int i=1; i<argc; i++){
        std::string arg = argv[i];

        if(arg == "-s" || arg == "--seed"){
            params.seed = std::stoi(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "-t" || arg == "--threads"){
            params.n_threads = std::stoi(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "-p" || arg == "--prompt"){
            params.prompt = get_next_arg(i, argc, argv, arg, params);
        } else if(arg == "-n" || arg == "--n_predict"){
            params.n_predict = std::stoi(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "-np" || arg == "--n_parallel"){
            params.n_parallel = std::stoi(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "--top-k"){
            params.top_k = std::stoi(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "--top-p"){
            params.top_p = std::stof(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "--temp"){
            params.temp = std::stof(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "--repeat-last-n"){
            params.repeat_last_n = std::stoi(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "--repeat-penalty"){
            params.top_p = std::stof(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "-b" || arg == "--batch_size"){
            params.n_batch = std::stoi(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "-c" || arg == "--context"){
            params.n_ctx = std::stoi(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "-ngl" || arg == "--gpu_layers"){
            params.n_gpu_layers = std::stoi(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "--ignore-eos" ){
            params.ignore_eos = true;
        } else if(arg == "-i" || arg == "--interactive"){
            params.interactive = true;
        } else if(arg == "-ip" || arg == "--interactive_port"){
            params.interactive = true;
            params.interactive_port = std::stoi(get_next_arg(i, argc, argv, arg, params));
        } else if(arg == "-tt" || arg == "--token_test"){
            params.token_test = get_next_arg(i, argc, argv, arg, params);
        } else {
            fprintf(stderr, "error: unknown argument %s.\n", arg.c_str());
            exit(0);
        }   
    }
    return true;
}