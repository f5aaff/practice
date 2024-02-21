# Cryptotraining Challenges

## Docker Setup

- Install Docker, e.g., via [Docker Desktop](https://www.docker.com/products/docker-desktop) or your favorite package manager.

- Open a terminal window and pull the cryptotraining image:

```
docker pull veorq/cryptotraining:v0
```

- Create a new directory on the host system for the cryptotraining exercises: 

```
mkdir $HOME/cryptotraining
```

- Run the cryptotraining Docker container, attach the exercise folder, and
  start a bash shell:

```
docker run --name cryptotraining --rm -it -v $HOME/cryptotraining:/usr/local/cryptotraining veorq/cryptotraining:v0
```

- All files you add to the exercise folder `$HOME/cryptotraining` on the host should become visible inside the Docker container at `/usr/local/cryptotraining` and vice versa. That way you can work on the exercises with your favorite editor on your host system and execute the code inside the Docker container.

- To exit the container simply type `exit` on its bash shell.
