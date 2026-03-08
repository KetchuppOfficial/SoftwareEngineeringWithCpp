# Building examples of Education repository

The whole process in encapsulated inside a Docker container.

## Build the image

Make sure the current work directory is 06-04-build-education.

```bash
podman build -t education .
```

## Run the container

```bash
podman run --rm -it education
```

## Results

![results](/06-04-build-education/images/results.png)
