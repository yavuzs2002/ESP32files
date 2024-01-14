import matplotlib.pyplot as plt
from skimage import io, color, exposure, filters

# Load a local image from file
image_path = r'C:\401\Codes\car2.PNG'
image = io.imread(image_path)

# Check if the image has an alpha channel (RGBA)
if image.shape[2] == 4:
    # Remove alpha channel
    image = image[:, :, :3]

# Step 1: Convert to grayscale
gray_image = color.rgb2gray(image)

# Step 2: Enhance contrast
enhanced_image = exposure.equalize_adapthist(gray_image)

# Step 3: Apply binary mask using edge detection
edges = filters.sobel(enhanced_image)
binary_mask = edges > 0.08  # You may need to adjust this threshold

# Plot each step
plt.figure(figsize=(12, 4))

plt.subplot(1, 4, 1)
plt.imshow(image)
plt.title('Original Image')
plt.axis('off')

plt.subplot(1, 4, 2)
plt.imshow(gray_image, cmap='gray')
plt.title('Grayscale')
plt.axis('off')

plt.subplot(1, 4, 3)
plt.imshow(enhanced_image, cmap='gray')
plt.title('Enhanced Contrast')
plt.axis('off')

plt.subplot(1, 4, 4)
plt.imshow(binary_mask, cmap='gray')
plt.title('Binary Mask')
plt.axis('off')

plt.show()
