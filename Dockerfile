FROM degoodmanwilson/cppbase-gcc54

MAINTAINER D.E. Goodman-Wilson

WORKDIR /app
ADD . /app
RUN conan install -s compiler=gcc -s compiler.version=5.4 -s compiler.libcxx=libstdc++11 --build=missing -o build_chancypolyhedra_tests=False -o build_chancypolyhedra_api=True
RUN conan build 
ENV PORT 80
EXPOSE 80
CMD ["/app/bin/chancypolyhedrad"]
