#!/usr/bin/env python
# coding: utf-8

## Setup Paths
WORKSPACE_PATH = '../Super Mario/HandControler/Tensorflow/workspace'
ANNOTATION_PATH = WORKSPACE_PATH+'/annotations'
MODEL_PATH = WORKSPACE_PATH+'/models'
CONFIG_PATH = MODEL_PATH+'/my_ssd_mobnet/pipeline.config'
CHECKPOINT_PATH = MODEL_PATH+'/my_ssd_mobnet/'


## import dependincies
import tensorflow as tf
from object_detection.utils import config_util
import os
from object_detection.utils import label_map_util
from object_detection.utils import visualization_utils as viz_utils
from object_detection.builders import model_builder
import keyboard
import cv2 
import numpy as np


##  Load Train Model From Checkpoint
def loadTrainModel():
    # Load pipeline config and build a detection model
    configs = config_util.get_configs_from_pipeline_file(CONFIG_PATH)
    detection_model = model_builder.build(model_config=configs['model'], is_training=False)

    # Restore checkpoint
    ckpt = tf.compat.v2.train.Checkpoint(model=detection_model)
    ckpt.restore(os.path.join(CHECKPOINT_PATH, 'ckpt-11')).expect_partial()
    return detection_model

@tf.function
def detect_fn(image, detection_model):
    image, shapes = detection_model.preprocess(image)
    prediction_dict = detection_model.predict(image, shapes)
    detections = detection_model.postprocess(prediction_dict, shapes)
    return detections


## Control the keyboard
def checkMovement(sign):
    if sign == 'right':
        #if keyboard.is_pressed('left'):
        keyboard.release('left')
        keyboard.press('right')
        
    elif sign == 'left':
        #if keyboard.is_pressed('right'):
        keyboard.release('right')
        keyboard.press('left')
        
    elif sign == 'jump':
        keyboard.send('space')
        
    elif sign == 'down':
        keyboard.send('down')
        
    elif sign == 'fire':
        keyboard.send('z')
        
    elif sign == 'standstill':
        #if keyboard.is_pressed('left'):
        keyboard.release('left')
        #if keyboard.is_pressed('right'):
        keyboard.release('right')


## Detect While Playing
def startDetection(detection_model):
    category_index = label_map_util.create_category_index_from_labelmap(ANNOTATION_PATH+'/label_map.pbtxt')

    # Setup capture
    cap = cv2.VideoCapture(0)
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    while True: 
        ret, frame = cap.read()
        image_np = np.array(frame)
    
        input_tensor = tf.convert_to_tensor(np.expand_dims(image_np, 0), dtype=tf.float32)
        detections = detect_fn(input_tensor, detection_model)
    
        num_detections = int(detections.pop('num_detections'))
        detections = {key: value[0, :num_detections].numpy()
                  for key, value in detections.items()}
        detections['num_detections'] = num_detections

        # detection_classes should be ints.
        detections['detection_classes'] = detections['detection_classes'].astype(np.int64)

        label_id_offset = 1
        image_np_with_detections = image_np.copy()

        viz_utils.visualize_boxes_and_labels_on_image_array(
                image_np_with_detections,
                detections['detection_boxes'],
                detections['detection_classes']+label_id_offset,
                detections['detection_scores'],
                category_index,
                use_normalized_coordinates=True,
                max_boxes_to_draw=5,
                min_score_thresh=.5,
                agnostic_mode=False)
    
        # Convert to keyboard press
        signID = detections['detection_classes'][0]+label_id_offset
        #if detections['detection_scores'][0] >= 0.8:
        checkMovement(category_index[signID]['name'])
    
        cv2.imshow('Hand Control',  cv2.resize(image_np_with_detections, (400, 400)))
    
        if cv2.waitKey(1) & 0xFF == ord('q'):
            cap.release()
            break


def main():
    detection_model = loadTrainModel()
    startDetection(detection_model)


if __name__ == '__main__':  
    main()