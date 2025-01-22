#include <time.h>
#include <iostream>
#include <vector>
#include "common.h"
#include "ggml.h"

// default hyper parameters for (GPT2-117M)
struct gpt2_hparams {
    int32_t n_vocab     = 50257;
    int32_t n_ctx       = 1024;
    int32_t n_embd      = 768;
    int32_t n_head      = 12;
    int32_t n_layer     = 12;
    int32_t ftype       = 1;
    float eps           = 1e-5f;       
};

struct gpt2_layer{
    // Layer normalization gamma and beta 
    struct ggml_tensor * ln_1_g;
    struct ggml_tensor * ln_1_b;
    
    struct ggml_tensor * ln_2_g;
    struct ggml_tensor * ln_2_b;

    // Attention weight matrix for calculating Q,K,V
    struct ggml_tensor * c_attn_attn_w;
    struct ggml_tensor * c_attn_attn_b;

    // Projects the output of attention to the model's dimensionality
    struct ggml_tensor * c_attn_proj_w;
    struct ggml_tensor * c_attn_proj_b;

    // mlp
    struct ggml_tensor * c_mlp_fc_w;
    struct ggml_tensor * c_mlp_fc_b;

    // Projects MLP output back to the model's dimensionality
    struct ggml_tensor * c_mlp_proj_w;
    struct ggml_tensor * c_mlp_proj_b;
};

struct gpt2_model {
    gpt2_hparams hparams;

    // normalization
    struct ggml_tensor * ln_f_g;
    struct ggml_tensor * ln_f_b;

    struct ggml_tensor * wte;       // token embedding
    struct ggml_tensor * wpe;       // positional embeddings
    struct ggml_tensor * lm_head;    // language model head

    std::vector<gpt2_layer> layers;

    // key + value memory
    struct ggml_tensor * memory_k;
    struct ggml_tensor * memory_v;

    struct ggml_context * ctx_w;
};

// loads model from file
bool gpt2_model_load(std::string & model_file, gpt2_model & model, gpt_vocab & vocab){

    return false;
}

int main(int argc, char ** argv){
    gpt_params params;
    params.model = "models/gpt-2-117M/ggml-model.bin";
    
    if(gpt_params_parse(argc, argv, params) == false){
        printf("Error parsing input...\n");
        return 1;
    }

    if (params.seed < 0){
        params.seed = time(NULL);
    }

    // __func__ is used to get the name of the current function
    printf("%s: seed = %d\n", __func__, params.seed);

    //if prompt is empty. don't do anything
    if (params.prompt.empty()){
        printf("Prompt is empty...\n");
        return 1;
    }

    gpt_vocab vocab;
    gpt2_model model;

    // load the model
    {
        if(!gpt2_model_load(params.model, model, vocab)){
            fprintf(stderr,"%s: Failed to load model from '%s'\n", __func__, params.model.c_str());
        }

        // test_gpt_tokenizer(vocab, params.token_test);
    }
}