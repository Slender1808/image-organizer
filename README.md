# Instalação

## Requirements

Python ≥ 3.6 ou Anaconda ≥ 4

G++ ou Clang++

### Python

```shell
pip install -r requirements.txt
```

OU

```shell
conda create -n tf-gpu tensorflow-gpu
```

### Build

### imagemagick

[https://imagemagick.org/script/magick++.php](https://imagemagick.org/script/magick++.php)

### C++
```shell
g++ `Magick++-config --cxxflags --cppflags` -O3 -o main main.cpp `Magick++-config --ldflags --libs`
```


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

[https://tfhub.dev/google/imagenet/nasnet_large/classification/5](https://tfhub.dev/google/imagenet/nasnet_large/classification/5)
