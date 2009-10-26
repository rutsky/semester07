color_01 = color 0 0 80
color_02 = color 255 255 255

stepsize_r = (color_02.r - color_01.r)/$.count
stepsize_g = (color_02.g - color_01.g)/$.count
stepsize_b = (color_02.b - color_01.b)/$.count

for i = 1 to $.count do (
  newColor = (color ((i*stepsize_r)+ color_01.r-stepsize_r) ((i*stepsize_g)+color_01.g-stepsize_g) ((i*stepsize_b)+color_01.b-stepsize_b))
  $[i].wirecolor = newColor
)
