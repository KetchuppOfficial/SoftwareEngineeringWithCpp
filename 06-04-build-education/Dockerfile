FROM ubuntu:24.04

RUN apt-get -y update

RUN apt-get install -y \
    cmake \
    wget \
    git \
    python3 \
    python3-dev

# install newest versions of gcc
RUN apt-get install -y \
    gcc-14 \
    g++-14

RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 100
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100

# getting boost sources
ARG boost_sources=https://sourceforge.net/projects/boost/files/boost/1.85.0/boost_1_85_0.tar.gz/download
ARG boost_build_options="toolset=gcc variant=release link=static runtime-link=static threading=multi"
RUN wget $boost_sources -O boost_1_85_0.tar.gz
RUN tar xvf boost_1_85_0.tar.gz
RUN cd boost_1_85_0 && bash bootstrap.sh
RUN cd boost_1_85_0 && ./b2 $boost_build_options -j8 install
RUN cd boost_1_85_0 && bash bootstrap.sh --with-python=python3
RUN cd boost_1_85_0 && ./b2 --with-python $boost_build_options -j8 install
RUN rm -rf boost_1_85_0 boost_1_85_0.tar.gz

# Install PDF-Writer
RUN apt-get install -y zlib1g-dev
RUN wget https://github.com/galkahana/PDF-Writer/archive/refs/tags/v4.8.1.tar.gz
RUN tar xvf v4.8.1.tar.gz
RUN cd PDF-Writer-4.8.1 && cmake -B build
RUN cd PDF-Writer-4.8.1 && cmake --build build -j4 --config Release
RUN cd PDF-Writer-4.8.1 && cmake --install build
RUN rm -rf PDF-Writer-4.8.1 v4.8.1.tar.gz

# Install zipper
RUN git clone https://github.com/Lecrapouille/zipper.git --recursive
RUN cd zipper && cmake -B build -DZIPPER_SHARED_LIB=ON -DZIPPER_BUILD_DEMOS=ON -DZIPPER_BUILD_TESTS=ON
RUN cd zipper && cmake --build build -j4 --config Release
RUN cd zipper && cmake --install build
RUN rm -rf zipper

# Install libpqxx
RUN apt-get install -y \
    libpq-dev \
    postgresql \
    postgresql-contrib
RUN wget https://github.com/jtv/libpqxx/archive/refs/tags/8.0.0.tar.gz
RUN tar xvf 8.0.0.tar.gz
RUN cd libpqxx-8.0.0 && cmake -B build
RUN cd libpqxx-8.0.0 && cmake --build build -j4 --config Release
RUN cd libpqxx-8.0.0 && cmake --install build
RUN rm -rf libpqxx-8.0.0 8.0.0.tar.gz

# Install glog
RUN git clone https://github.com/google/glog
RUN cd glog && cmake -B build
RUN cd glog && cmake --build build -j4 --config Release
RUN cd glog && cmake --install build
RUN rm -rf glog

# Install gbenchmark
RUN wget https://github.com/google/benchmark/archive/refs/tags/v1.9.5.tar.gz
RUN tar xvf v1.9.5.tar.gz
RUN cd benchmark-1.9.5 && cmake -B build -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release
RUN cd benchmark-1.9.5 && cmake --build build -j4 --config Release
RUN cd benchmark-1.9.5 && cmake --install build
RUN rm -rf benchmark-1.9.5 v1.9.5.tar.gz

# Install other dependencies
RUN apt-get install -y \
    libgtest-dev \
    libicu-dev \
    nlohmann-json3-dev \
    libtbb-dev \
    g++-14-multilib \
    vim

RUN useradd -ms /bin/bash user
USER user
WORKDIR /home/user

RUN git clone https://github.com/i-s-m-mipt/Education.git
COPY education.patch education.patch
RUN cd Education && git apply ../education.patch

RUN mkdir -p Education/libraries

# Build library_v1
RUN cd Education/projects/library_v1 && cmake -B build && cmake --build build
RUN cp Education/projects/library_v1/build/libstatic.a ~/Education/libraries

# Build library_v2
RUN cd Education/projects/library_v2 && cmake -B build && cmake --build build
RUN cp Education/projects/library_v2/build/libshared.so ~/Education/libraries

# Build examples
RUN cd Education/projects/examples && cmake -B build && cmake --build build -j4

# Build examples requiring C++ modules
RUN cd Education/projects/examples/build && \
    g++ -c -std=c++23 -Wall -Wextra -Wpedantic -O0 ../source/06.06.hpp -o ../source/06.06.hpp.gch && \
    g++ -std=c++23 -Wall -Wextra -Wpedantic -O0 ../source/06.07.cpp ../source/06.08.cpp -ltbb -o 06.08 && \
    rm ../source/06.06.hpp.gch

RUN cd Education/projects/examples/build && \
    g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -Wpedantic -O0 -xc++-system-header print && \
    g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -Wpedantic -O0 ../source/06.15.cxx && \
    g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -Wpedantic -O0 ../source/06.13.cxx && \
    g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -Wpedantic -O0 ../source/06.14.cxx && \
    g++ -std=c++23 -fmodules-ts -Wall -Wextra -Wpedantic -O0 ../source/06.16.cpp 06.13.o 06.14.o 06.15.o -o 06.16
