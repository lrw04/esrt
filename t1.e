v 0.2 0.2 0.2
t solid-color color -1 e
m lambertian albedo -1 fuzz 0.3 e
v 1000 0 1000
v -1000 0 1000
v -1000 0 -1000
v 1000 0 -1000
o triangle -1 -2 -3 -1
o triangle -3 -4 -1 -1
v -1.5 1 -2
v 1.5 1 0
v 0.2 0.8 0.2
v 0.2 0.2 0.8
t solid-color color -2 e
t solid-color color -1 e
m reflective albedo -2 fuzz 0.1 e
m lambertian albedo -1 e
o sphere -4 1 -2
o sphere -3 1 -1 
v 10 10 10
t solid-color color -1 e
m diffuse-light emission -1 e
v 4 3 4
o sphere -1 1 -1
v 0 -1000 0
o sphere -1 1000 0
v 0 3000 0
o sphere -1 1000 -1
o union 0 1 2 3 4 e
v 0 1 3
v 0 1 0
v 0 0 -1
c origin -3 up -2 direction -1 aspect-ratio 1 fov 120d e
r object -1 camera -1 width 1024 samples 128 max-depth 8 gamma 2 png-out image-128.png e
e
r object -1 camera -1 width 1024 samples 4096 max-depth 8 gamma 2 png-out image-4096.png e
