FROM degoodmanwilson/luna:5.0.4

MAINTAINER D.E. Goodman-Wilson

ENV PORT 80
EXPOSE 80
ADD --chown=conan:1001 . /app
WORKDIR /app
RUN conan --version
RUN conan remote add catch https://api.bintray.com/catchorg/catch2
RUN conan install . --build=missing
RUN cmake .
RUN cmake --build .
CMD ["./bin/chancypolyhedra"]
