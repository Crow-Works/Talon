# Talon Package Manager

## Description

Talon is a lightweight package manager designed specifically for managing dependencies for the Raven Game Engine. It simplifies the process of fetching, compiling, and managing dependencies necessary for development.

## Features

- **Dependency Management**: Talon allows developers to specify dependencies in a simple YAML configuration file, making it easy to define and manage project dependencies.
  
- **Automatic Compilation**: Talon automatically downloads and compiles dependencies, minimizing manual intervention and streamlining the development process.
  
- **Cross-platform Compatibility**: Talon is designed to work seamlessly across different platforms, ensuring consistent behavior regardless of the development environment.

## Usage:

To utilize Talon for managing dependencies in the Raven Engine project, follow these steps:

1. **Create a Configuration File:** Start by creating a `dependencies.yaml` file in the root directory of your Raven Engine project. Define your dependencies and their download URLs in this YAML file.

2. **Run Talon:** Execute Talon from the command line, passing the name of the configuration file as an argument.

   ```bash
   ./Talon dependencies.yaml
   ```

   This command triggers Talon to read the `dependencies.yaml` file, download the specified dependencies, compile them (if necessary), and integrate them into the Raven Engine project.

## YAML Configuration

Below is an example YAML configuration file demonstrating the structure for specifying dependencies and configuration options:

```yaml
# dependencies.yaml

Config:
  DependencyDir: # Directory where dependencies are downloaded
  BuildDir: # Directory where dependencies are built
  LibraryDir: # Directory where compiled libraries are stored
  RemoveBuildDir: true   # Set to true if you want to remove the build directory after compilation

Dependencies:
  Dependency1: url1
  Dependency2: url2
  Dependency3: url3
  ...
```

- `DependencyDir`: Specifies the directory where dependencies will be downloaded.
- `BuildDir`: Specifies the directory where dependencies will be built.
- `LibraryDir`: Specifies the directory where compiled libraries will be stored.
- `RemoveBuildDir`: Specifies whether to remove the build directory after compilation. Set to true to remove the build directory, or false to keep it.

### Note
This is currently only supporting git repositories
