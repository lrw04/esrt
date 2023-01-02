# camera
v 278 273 -800
v 0 0 1
v 0 1 0
c origin -3 up -1 direction -2 aspect-ratio 1 fov 0.6860478808414068 e

v 0.65 0.05 0.05            # red
v 0.73 0.73 0.73            # grey
v 0.12 0.45 0.15            # green
v 15 15 15                  # light
t solid-color color -4 e
t solid-color color -3 e
t solid-color color -2 e
t solid-color color -1 e
m lambertian albedo -4 e
m lambertian albedo -3 e
m lambertian albedo -2 e
m diffuse-light emission -1 e

# floor
v 552.8 0 0
v 0 0 0
v 0 0 559.2
v 549.6 0 559.2
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

# back-wall
v 549.6 0 559.2
v 0 0 559.2
v 0 548.8 559.2
v 556 548.8 559.2
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

# ceiling
v 0 548.8 559.2
v 556 548.8 559.2
v 556 548.8 0
v 0 548.8 0

v 213 548.8 332
v 343 548.8 332
v 343 548.8 227
v 213 548.8 227
o triangle -8 -7 -4 1
o triangle -7 -3 -4 1
o triangle -7 -6 -3 1
o triangle -6 -2 -3 1
o triangle -6 -5 -2 1
o triangle -5 -1 -2 1
o triangle -5 -8 -1 1
o triangle -8 -4 -1 1

# light
o triangle -4 -3 -2 3
o triangle -2 -1 -4 3

# left-wall
v 552.8 0 0
v 549.6 0 559.2
v 556 548.8 559.2
v 556 548.8 0
o triangle -4 -3 -2 0
o triangle -2 -1 -4 0

# right-wall
v 0 0 559.2
v 0 0 0
v 0 548.8 0
v 0 548.8 559.2
o triangle -4 -3 -2 2
o triangle -2 -1 -4 2

# short-block
v 130.0 165.0  65.0 
v  82.0 165.0 225.0
v 240.0 165.0 272.0
v 290.0 165.0 114.0
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

v 290.0   0.0 114.0
v 290.0 165.0 114.0
v 240.0 165.0 272.0
v 240.0   0.0 272.0
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

v 130.0   0.0  65.0
v 130.0 165.0  65.0
v 290.0 165.0 114.0
v 290.0   0.0 114.0
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

v  82.0   0.0 225.0
v  82.0 165.0 225.0
v 130.0 165.0  65.0
v 130.0   0.0  65.0
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

v 240.0   0.0 272.0
v 240.0 165.0 272.0
v  82.0 165.0 225.0
v  82.0   0.0 225.0
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

# tall-block
v 423.0 330.0 247.0
v 265.0 330.0 296.0
v 314.0 330.0 456.0
v 472.0 330.0 406.0
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

v 423.0   0.0 247.0
v 423.0 330.0 247.0
v 472.0 330.0 406.0
v 472.0   0.0 406.0
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

v 472.0   0.0 406.0
v 472.0 330.0 406.0
v 314.0 330.0 456.0
v 314.0   0.0 456.0
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

v 314.0   0.0 456.0
v 314.0 330.0 456.0
v 265.0 330.0 296.0
v 265.0   0.0 296.0
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

v 265.0   0.0 296.0
v 265.0 330.0 296.0
v 423.0 330.0 247.0
v 423.0   0.0 247.0
o triangle -4 -3 -2 1
o triangle -2 -1 -4 1

o union 0~37 e

r object -1 camera 0 width 512 samples 512 max-depth 4 gamma 1 png-out cb.png e
