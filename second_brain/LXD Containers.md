---
tags:
  - Linux
  - Containers
  - Computing
created: 2023-03-22T22:54
updated: 2025-07-23T20:26
---
- [Creating a Centos7 instance](#Creating%20a%20Centos7%20instance)
- [Create a storage pool](#Create%20a%20storage%20pool)
- [Maintenance](#Maintenance)
- [Getting a list of containers](#Maintenance#Getting%20a%20list%20of%20containers)
- [Logging into a container](#Maintenance#Logging%20into%20a%20container)
- [Setting limits](#Maintenance#Setting%20limits)


LXD containers provide a layer above the LXC level. This provides tools to encapsulate the details at the LXC level.

LXD should probably be installed using snap, as this is the suggested way to get the latest stable version.

```
sudo snap install lxd
```

You will need to be added to the lxd group in order to interact with the containers:
```
sudo usermod <username> -a -G lxd
```

### Creating a Centos7 instance
Next, we need to create a new instance using the centos7 image and a directory for storage:
```
lxd init
```
This method will go through an interactive setup. In our case, the one big non-default

### Create a storage pool
We need to create a storage pool in order to store all of the container files:
```
lxc storage create pool1 dir source=/CHAIM2/CHAIM_LXD
```

We can now use this pool when we create our containers.
```
lxc launch <image> <instance_name> --storage <storage_pool>
```

where the image could be something like images:centos7. Once your new instance has launched, create a new chaim user.

## Maintenance
### Getting a list of containers
We can get a list of containers with:
```
lxc list
```
### Logging into a container
You can log into a container with
```
lxc console centos01
```
You may need to hit enter before you login. Your user needs to be in the lxd group. You can add them with the command
```
sudo usermod <username> -a -G lxd
```
### Setting limits
You can set limits for various elements with
```
lxc config set centos01 limits.cpu=44
lxc config set centos01 limits.memory=121GiB
```
You may need to restart the container with
```
lxc restart centos01
```
### Setting the locale
The locale does not get set when you exec a bash shell. In order to have it always be set, you can change the configuration for a container with
```
lxc config set CONTAINER environment.LC_ALL=en_US.UTF-8
```

### Listing all available remote images
You can get a list of all of the standard remote images with
```
lxc image list images:
```
You can then grep this list if you are looking for something specific.