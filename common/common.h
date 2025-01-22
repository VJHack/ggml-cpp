#include <thread>
#include <vector>
#include <map>

//
// GPT CLI argument parsing
//
struct gpt_params{
    int32_t seed        = -1;       // Random Number Generator (RNG) Seed
    int32_t n_threads   = std::min(4, (int32_t) std::thread::hardware_concurrency()); // Number of Threads
    int32_t n_predict   = 200;      // New tokens to predict
    int32_t n_parallel  = 1;        // number of parallel streams
    int32_t n_batch     = 32;       // batch size for prompt processing
    int32_t n_ctx       = 2048;     // context size (max size of KV cache)
    int32_t n_gpu_layers= 0;        // number of layers to offload to gpu

    bool ignore_eos     = false;    // ignore EOS token when generating text

    // sampling parameters
    int32_t top_k           = 40;
    float   top_p           = 0.9f;
    float   temp            = 0.9f;
    int32_t repeat_last_n   = 64;
    float   repeat_penalty  = 1.00f;

    std::string model       = "models/gpt-2-117M/ggml-model.bin";  //model path
    std::string prompt      = "";
    std::string token_test  = "";

    bool        interactive         = false;
    int32_t     interactive_port    = -1;
};

bool gpt_params_parse(int argc, char ** argv, gpt_params & params);

struct gpt_vocab {
    //using is a way of type aliasing, so it would be used like this: using new_type_name = existing_type;
    using id    = int32_t;
    using token = std::string;

    std::map<id, token> id_to_token;
    std::map<token, id> token_to_id;
    std::vector<std::string> special_tokens;

    void add_special_tokens(const std::string & token);
};