# Instalação

## Requirements

Python ≥ 3.6 ou Anaconda ≥ 4

### Python

```shell
conda create -n tf-gpu tensorflow-gpu
```

### Build

## Run

```shell
find /home/jadson/Documentos/test -type f | xargs -n1 ./test /home/jadson/Imagens/
```

OU

```shell
conda activate tf-gpu

find /home/jadson/Documentos/test -type f | xargs -n1 ./test /home/jadson/Imagens/
```

## Model

[https://tfhub.dev/google/imagenet/mobilenet_v3_large_100_224/feature_vector/5](https://tfhub.dev/google/imagenet/mobilenet_v3_large_100_224/feature_vector/5)
