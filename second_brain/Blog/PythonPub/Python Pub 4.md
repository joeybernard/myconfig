## Python Pub 4

---
## pytorch intro

---
### Installation
- installation depends on
	- CPU type
	- OS
	- AMD or Nvidia GPU or no GPU
---
### Library Types
- There are domain-specific libraries, like
	- TorchText
	- TorchVision
	- TorchAudio
	- etc
---
### Tensors
- tensors are like numpy ndarrays
- they both have accelerated functions
- tensors also have accelerated functions that use GPUs
---
### Initialisation
```python
import torch

device = torch.device("cpu")
# OR
# device = torch.device("cude:0")

data1 = torch.tensor([1, 2, 3])
```
Then you can call torch functions and have them run on the initialised device
---
### nn
- nn is the sub-module that provides code to work with neural nets
- this is how you can define a model that you want to use
- this is defined as a sequence of layers
- you can write manual code to do forward and backward passes in order to adjust weights
---
### optim
- a sub-module to encapsulate the optimisation steps so that they can be treated as a single step
- there are a number of pre-defined optimisations available
- still use nn to define the model
---
### Reinforcement Learning
- you can do this with raw torch
- there is also TorchRL to simplify some of the steps
- you define a neural network, and have input data with expected outcomes
- you use reinforcement learning to do the training of the model
---
### Tunings
- you can define parameterizations within the layers
- you can do prunings to reduce the size of the models
- you can use model ensembling to combine multiple models together
- you can use knowledge distillation to effectively export a large model to a smaller model that still generates appropriate output