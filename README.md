# C Image to Ascii
Creates an Ascii txt file when provided an image.

# How does it work?
I converted the image to a list of pixels using the Image Parsing library. I then calculate the relative luminance of every pixel based on the formular:
`0.2126 * R + 0.7152 * G + 0.0722 * B`
Then with the calculated relative luminance, I try to match it with the ascii character that have the relative brightness.
These are the ASCII characters used from darkest to lightest:
`$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. `

And I write the ASCII to a text file.
