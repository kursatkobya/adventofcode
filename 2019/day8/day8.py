from typing import List


def separate_layers(width: int, height: int, source: List[int]) -> List[int]:
    layers = [source[i:i + (width * height)] for i in
              range(0, len(data), (width * height))]
    return layers


def show_must_go_on(size: int, layers: List[int]) -> List[int]:
    pixels = []
    for x in range(size):
        for layer in range(len(layers)):
            if layers[layer][x] != 2:
                pixels.append(layers[layer][x])
                break
    return pixels


data: List[int]
with open('input') as f:
    data = [int(i) for i in f.readline().strip()]

layers = separate_layers(25, 6, data)
least = min(layers, key=lambda layer: layer.count(0))

print(least.count(1) * least.count(2))
pixels = show_must_go_on(150, layers)
image = [pixels[i: i + 25] for i in range(0, len(pixels), 25)]
for row in image:
    print(''.join(['█' if p == 1 else ' ' for p in row]))
