import os
os.environ["TF_CPP_MIN_LOG_LEVEL"] = '2'

import tensorflow as tf
import tensorflow_hub as hub

from PIL import Image
import numpy as np

def preprocess_image(image):
    image = np.array(image)
    # reshape into shape [batch_size, height, width, num_channels]
    img_reshaped = tf.reshape(
        image, [1, image.shape[0], image.shape[1], image.shape[2]])
    # Use `convert_image_dtype` to convert to floats in the [0,1] range.
    image = tf.image.convert_image_dtype(img_reshaped, tf.float32)
    return image


def load_image(image_url):
    fd = tf.io.gfile.GFile(image_url, 'rb')
    img = preprocess_image(Image.open(fd))
    if tf.reduce_max(img) > 1.0:
        img = img / 255.
    if len(img.shape) == 3:
        img = tf.stack([img, img, img], axis=-1)
    return img

# download labels and creates a maps
#labels_file = "https://storage.googleapis.com/download.tensorflow.org/data/ImageNetLabels.txt"
#downloaded_file = tf.keras.utils.get_file("labels.txt", origin=labels_file)

img_url = "/tmp/t2/input.png"
image = load_image(img_url)

# Salvando modelo local
#nasnet_large
model_handle = "https://tfhub.dev/google/imagenet/nasnet_large/classification/5"
classifier = hub.load(model_handle)
#tf.saved_model.save(classifier, '/tmp/adder')

#classifier = tf.saved_model.load('./nasnet_large')

# Run model on image
result = classifier(image)
#probabilities = tf.nn.softmax(result).numpy()

# Salvando resultado
np.savetxt("/tmp/t2/out.csv", result, fmt='%u', delimiter='\n')
