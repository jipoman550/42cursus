FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    clang \
    make \
    gdb \
    valgrind \
    libreadline-dev \
    pkg-config \
    git \
    vim \
    nano \
 && rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash student
WORKDIR /work
RUN chown -R student:student /work
USER student

ENV CC=clang \
    CFLAGS="-Wall -Wextra -Werror -g"

CMD ["/bin/bash"]
