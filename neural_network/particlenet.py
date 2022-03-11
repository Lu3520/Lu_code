#reference : Graph Neural Networks (GNN) using Pytorch Geometric | Stanford University[https://www.youtube.com/watch?v=-UjytpbqX4A&t=2506s]
#partcilenet : https://cms-ml.github.io/documentation/inference/particlenet.html
import torch
import torch.nn as nn
import torch.nn.functional as F

import torch_geometric.nn as pyg_nn
import torch_geometric.utils as pyg_utils

import time
from datetime import datetime

import networkx as nx
import numpy as np
import torch
import torch.optim as optim

from torch_geometric.datasets import TUDataset
from torch_geometric.datasets import Planetoid
from torch_geometric.data import DataLoader

import torch_geometric.transforms as T

from tensorboardX import SummaryWriter
from sklearn.manifold import TSNE
import matplotlib.pyplot as plt

class ParticleNet(nn.Module):
  def __init__(self, input_dim, hidden_dim, output_dim):
      super(ParticleNet, self).__init__()
      self.convs = nn.ModuleList()
      #first conv block
      self.convs.append(self.pyg_nn.GCNConv(input_dim, 64))
      self.convs.append(self.pyg_nn.GCNConv(64, 32))
      self.convs.append(self.pyg_nn.GCNConv(32, 64))
      #second conv block
      self.convs.append(self.pyg_nn.GCNConv(64, 128))
      self.convs.append(self.pyg_nn.GCNConv(128, 64))
      self.convs.append(self.pyg_nn.GCNConv(64, 128))
      #third conv block
      self.convs.append(self.pyg_nn.GCNConv(128, 256))
      self.convs.append(self.pyg_nn.GCNConv(256, 128))
      self.convs.append(self.pyg_nn.GCNConv(128, 256))
      #MLP
      self.post_mp = nn.Sequential(
          nn.Linear(256, 512), nn.ReLU(), nn.Dropout(0.1),
          nn.Linear(512, 2), nn.ReLU(), nn.Dropout(0.5))

  def forward(self, data):
      x, edge_index, batch = data.x, data.edge_index, data.batch
      if data.num_node_features == 0:
        x = torch.ones(data.num_nodes, 1)

      x_ini = x
      for i in range(9):
          if i%3 is 0: x_ini = x
          x = self.convs[i](x, edge_index)
          x = F.relu(x)
          x = F.dropout(x, p=0.3, training=self.training)
          x = nn.BatchNorm2d(x)
          if (i+1)%3 is 0: x = x + x_ini

      x = pyg_nn.global_mean_pool(x, batch)
      x = self.post_mp(x)

      return F.log_softmax(x, dim=1)

  def loss(self, pred, label):
      return F.nll_loss(pred, label)
    
#not finish yet in this code for particlenet model.
