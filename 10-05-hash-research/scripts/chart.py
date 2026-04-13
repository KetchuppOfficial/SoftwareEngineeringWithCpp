import json
import math
import argparse
import numpy as np
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description="Plot bar charts from JSON data")
parser.add_argument("--input", required=True, help="Path to input JSON file")
parser.add_argument("--xmax", type=int, required=True, help="Maximum value on the X-axis")
parser.add_argument("--output", required=True, help="Path to output image file")

args = parser.parse_args()

with open(args.input, "r") as f:
    data = json.load(f)

num_charts = len(data)

cols = math.ceil(math.sqrt(num_charts))
rows = math.ceil(num_charts / cols)

fig, axes = plt.subplots(rows, cols, figsize=(5 * cols, 4 * rows))
axes = axes.flatten() if num_charts > 1 else [axes]

for ax, (name, values) in zip(axes, data.items()):
    x_labels = sorted(values.keys(), key=lambda k: int(k))
    x = [int(k) for k in x_labels]
    y = [values[k] for k in x_labels]

    ax.bar(x, y)
    ax.set_title(name)
    ax.set_xlabel("Buckets")
    ax.set_ylabel("Collisions")

    ax.set_xlim(0, args.xmax)

    tick_positions = np.linspace(0, args.xmax, 10)
    tick_labels = [str(int(round(p))) for p in tick_positions]

    ax.set_xticks(tick_positions)
    ax.set_xticklabels(tick_labels)

for i in range(num_charts, len(axes)):
    fig.delaxes(axes[i])

plt.tight_layout()

plt.savefig(args.output)
