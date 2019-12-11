from typing import List

def least_zero_layer(width: int, height: int, source: List[int]) -> List[int]:
    layers = [source[i:i + (width * height)] for i in
                range(0, len(data), (width * height))]
    return min(layers, key = lambda layer: layer.count(0))


data: List[int]
with open('input') as f:
    data = [int(i) for i in f.readline().strip()]

least = least_zero_layer(25, 6, data)
print(least.count(1) * least.count(2))
