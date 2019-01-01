FROM ubuntu:16.04

RUN apt-get update
RUN apt-get install -y git flex bison libreadline-dev vim

RUN git config --global user.email "daltonfury42@disroot.org"
RUN git config --global user.name "Dalton Fury"

# sudo docker build -t compilerenv .
# sudo docker run -v ~/codes/compiler-reborn:/root/ -it compilerenv



