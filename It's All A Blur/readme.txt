CSCI 103 Image Filtering Programming Assignment 

Name: Ethan Feng

Email Address: eyfeng@usc.edu

Answer the questions posed in the writeup below.

NOTE: It is helpful if you write at most 80 characters per line,
and avoid including special characters, so we can read your responses.

Please summarize the help you found useful for this assignment, which
may include office hours, discussion with peers, tutors, et cetera.
Saying "a CP on Tuesday" is ok if you don't remember their name.
If none, say "none".

: a Cp on Monday

================================ Questions ==================================

1. Padding design: If we restrict the size of the Gaussian kernels to odd 
integers between 3 and 11 inclusive, and we only allow 256x256 pixel images, 
what is the size of the largest padded image needed to handle padding with 
any kernel size? At what index will the upper-left pixel of the original 
image be placed in the padded image (answer in terms of N, the kernel size)? 
At what index in the padded array will the lower-right pixel of the original 
image be placed?

: The largest padded image needed to handle is a 256+11X256+11 pixel image. 
The coordinate of the upper-left pixel is (N/2, N/2), and the coordinate
of the lower-right pixel is(256+N/2, 256+N/2)

2. Kernel Design: Manually compute the raw and normalized Gaussian kernels 
for N=3, sigma=2. Use 4 decimal places. Discuss what would happen to the 
image if we used the raw kernel values.

: 0.4589 0.8825 0.4589    0.0720 0.1386 0.0720
  0.8825 1      0.8825    0.1386 0.1570 0.1386
  0.4589 0.8825 0.4589    0.0720 0.1386 0.0720
The image would get brighter (super bright) because the raw kernel values
sdd up to a value greater than one. 


3. Experimenation:  Provide the results for ALL experiments listed in the
                    writeup.

: The bluriness of the image as N increases for Gaussian blur filter. The 
sobel filter only emphasizes the edges on the images. No, the image doesn't
turn back to the original image since the blurring the image also means it
blur all the edges that're suppose to be in unsharp. 


4. Express in mathematical terms how the number of calculations your 
 program performs grows with the size, N, of the kernel.

: N^2 since the kernal size changes as N changes


================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

: 7-8 hours

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

: 

Do you have any other remarks?

:
