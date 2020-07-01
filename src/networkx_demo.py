# Python program to create an undirected 
# graph and add nodes and edges to a graph 
import networkx as nx 
import matplotlib.pyplot as plt
from networkx.drawing.nx_pydot import write_dot
from networkx.drawing.nx_agraph import graphviz_layout

# To create an empty undirected graph 
G = nx.Graph() 

# To add a node 
G.add_node(1) 
G.add_node(2) 
G.add_node(3) 

# To add an edge 
# Note graph is undirected 
# Hence order of nodes in edge doesn't matter 
G.add_edge(1,2) 
G.add_edge(3,1) 

# To get all the nodes of a graph 
node_list = G.nodes() 
print(node_list) 

# To get all the edges of a graph 
edge_list = G.edges() 
print(edge_list) 

name='demo'
print(list(nx.connected_components(G)))
pos = nx.nx_agraph.graphviz_layout(G)
plt.subplot(121)
nx.draw(G,node_color = 'red', pos=pos,with_labels=True)
plt.show()
plt.savefig(name+'.png')
write_dot(G, name+'.dot')
# the above command generates a dot file which we can convert to 
    #a dependency graph using command dot -Tps graph.dot -o  graph.ps
