FROM gcc:11.3.0
WORKDIR /app
COPY . /app
RUN g++ -o src/reader src/reader.cpp
RUN g++ -o src/writer src/writer.cpp
RUN chmod +x run.sh
CMD ["./run.sh"]