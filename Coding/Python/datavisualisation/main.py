from random import choice
import matplotlib.pyplot as plt

class RandomWalk:

    def __init__(self, num_points=5000):
        self.num_points = num_points
        self.x_values = [0]
        self.y_values = [0]

    def get_step(self):
        while len(self.x_values) < self.num_points:
            x_direction = choice([1, -1])
            x_distance = choice([0,1,2,3,4,5,6,7,8])
            x_step = x_distance * x_direction

            y_direction = choice([1, -1])
            y_distance = choice([0,1, 2, 3, 4, 5, 6, 7, 8])
            y_step = y_distance * y_direction
            if x_step == 0 and y_step == 0:
                continue
            return x_step,y_step

    def fill_walk(self):
        while len(self.x_values) < self.num_points:
            x_step, y_step = self.get_step()
            #adding new values of x and y into the list
            x = self.x_values[-1] + x_step
            y = self.y_values[-1] + y_step
            self.x_values.append(x)
            self.y_values.append(y)

rw = RandomWalk()
rw.fill_walk()
plt.style.use('classic')
fig, ax = plt.subplots(figsize=(10, 6), dpi=128)
point_numbers = range(rw.num_points)
ax.plot(rw.x_values, rw.y_values, linewidth=1)
ax.set_aspect('equal')
ax.get_xaxis().set_visible(False)
ax.get_yaxis().set_visible(False)
#emphasizing on the first and the last point
ax.scatter(0, 0, c='green', edgecolors='none', s=100)
ax.scatter(rw.x_values[-1], rw.y_values[-1], c='red', edgecolors='none', s=100)
plt.show()