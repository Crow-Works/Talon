# Talon Package Manager

## Description

Talon is a lightweight package manager designed specifically for managing dependencies for the Raven Game Engine. It simplifies the process of fetching, compiling, and managing dependencies necessary for development.

## Features

- **Dependency Management**: Talon allows developers to specify dependencies in a simple YAML configuration file, making it easy to define and manage project dependencies.
  
- **Automatic Compilation**: Talon automatically downloads and compiles dependencies, minimizing manual intervention and streamlining the development process.
  
<!--- **Efficient Caching**: Talon intelligently caches downloaded packages, optimizing build times and reducing network bandwidth usage during subsequent builds.-->
  
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

Below is an example YAML configuration file demonstrating the structure for specifying dependencies:

```yaml
# dependencies.yaml

Dependencies:
    Dependency1: url1
    Dependency2: url2
    Dependency3: url3
    ...
```

