#%%
import matplotlib.pyplot as plt
import numpy as np

interp_points = np.loadtxt("result.csv",delimiter=',')
# %%
plt.plot(interp_points[:,0],interp_points[:,1])
plt.show()
# %%
