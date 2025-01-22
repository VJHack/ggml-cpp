## ggml-cpp
ggml-cpp is an application that enables inference of open-source language models on CPU with the goal of experimenting with new ideas and supporting as many models as possible. ggml-cpp differs from llama.cpp as it is very slim, experimental, and only supports a cpu backend at the moment. This project was built with a simplicity-first mindset to make it easier to implement new ideas and techniques.

### Currently Supported Models:
- gpt2 (wip)

### Build
```
make gpt2
./download-ggml-model.sh 117M
```
### Run
```
./gpt2 --prompt "What is the meaning of life?"
```
