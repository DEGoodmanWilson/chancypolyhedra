FROM degoodmanwilson/luna-node

MAINTAINER D.E. Goodman-Wilson

ENV PORT 80
EXPOSE 80
WORKDIR /app
RUN conan --version
RUN conan install --build=missing
RUN cmake .
RUN cmake --build .
WORKDIR /app/site-source
RUN npm install
RUN npm run build
WORKDIR /app
CMD ["./bin/chancypolyhedrad"]
