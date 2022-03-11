import numpy as np
import tensorflow as tf
from tensorflow.keras import datasets, layers, models
import matplotlib.pyplot as plt
from tensorflow import keras
import matplotlib
matplotlib.use('Agg')

def show_history(history):
    fig, ax = plt.subplots(1, 2, figsize=(15,5))
    ax[0].set_title('loss')
    ax[0].plot(history.epoch, history.history["loss"], label="Train loss")
    ax[0].plot(history.epoch, history.history["val_loss"], label="Validation loss")
    ax[1].set_title('acc')
    ax[1].plot(history.epoch, history.history["accuracy"], label="Train acc")
    ax[1].plot(history.epoch, history.history["val_accuracy"], label="Validation acc")
    ax[0].legend()
    ax[1].legend()
    return fig
    
def cluster_track_intensity_arr(cluster_arr, track_arr):
    arr_len = len(cluster_arr)
    output_arr = np.zeros((16*16*arr_len*2), dtype=float).reshape(arr_len,16,16,2)
    for i in range(0, arr_len):
        for row in range(0,16):
            for col in range(0,16):
                    output_arr[i][row][col][0] = cluster_arr[i][row][col]
                    output_arr[i][row][col][1] = track_arr[i][row][col]
    return output_arr

def label_trans(arr):
    arr_len = len(arr)
    output_arr = np.zeros((arr_len), dtype=float).reshape(arr_len,1)
    for i in range(0, arr_len):
        output_arr[i][0] = arr[i]
    return output_arr

# DNN
regularization_Lambda = 0.00000001
input_DNN = tf.keras.layers.Input(shape=(31,))
DNN_dense_1 = tf.keras.layers.Dense(64, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(input_DNN)
DNN_drop_1 = tf.keras.layers.Dropout(0.3)(DNN_dense_1)
DNN_dense_2 = tf.keras.layers.Dense(64, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(DNN_drop_1)
DNN_drop_2 = tf.keras.layers.Dropout(0.3)(DNN_dense_2)

# CNN
regularization_Lambda = 0.00000001
input_CNN = tf.keras.layers.Input(shape=(16, 16, 2))
CNN_conv2d_1 = tf.keras.layers.Conv2D(256, (7, 7), activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(input_CNN)
CNN_drop_1 = tf.keras.layers.Dropout(0.3)(CNN_conv2d_1)
CNN_conv2d_2 = tf.keras.layers.Conv2D(128, (5, 5), activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(CNN_drop_1)
CNN_drop_2 = tf.keras.layers.Dropout(0.3)(CNN_conv2d_2)
CNN_conv2d_3 = tf.keras.layers.Conv2D(64, (3, 3), activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(CNN_drop_2)
CNN_drop_3 = tf.keras.layers.Dropout(0.3)(CNN_conv2d_3)
CNN_Maxpooling_1 = tf.keras.layers.MaxPooling2D((2, 2))(CNN_drop_3)
CNN_flatten_1 = tf.keras.layers.Flatten()(CNN_Maxpooling_1)
CNN_dense_1 = tf.keras.layers.Dense(128, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(CNN_flatten_1)
CNN_drop_4 = tf.keras.layers.Dropout(0.3)(CNN_dense_1)

# Concatenate
concat = tf.keras.layers.Concatenate()([DNN_drop_2, CNN_drop_4])
# output
front = tf.keras.layers.Dense(192)(concat)
output = tf.keras.layers.Dense(2)(front)

full_model = tf.keras.Model(inputs=[input_DNN, input_CNN], outputs=[output])
full_model.summary()

#loss function
loss_fn = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True)
#optimizer
opt = keras.optimizers.Adam(learning_rate=0.00001)
full_model.compile(optimizer=opt, loss=loss_fn, metrics=['accuracy'])

#callback
callback = tf.keras.callbacks.EarlyStopping(monitor='val_loss', patience=20)

cluster_fname = '/home/chengyu/paper/front_jet/root_numpy/array_save/s_cluster/'

# DNN
#input training file
input_fname = '/home/chengyu/paper/front_jet/DNN/output/arrayfile/'
#train_sample
with open(input_fname + 'trainfile_le21_flat_scalar.npy', 'rb') as file2_1_scalar_f:
    DNN_train_sample = np.load(file2_1_scalar_f)
    
with open(input_fname + 'trainfile_le21_flat_label.npy', 'rb') as file2_1_label_f:
    DNN_train_label = np.load(file2_1_label_f)
    
#input test sample
with open(input_fname + 'testfile_le21_flat_scalar.npy', 'rb') as file2_5_scalar_f:
    DNN_test_sample = np.load(file2_5_scalar_f)

with open(input_fname + 'testfile_le21_flat_label.npy', 'rb') as file2_5_label_f:
    DNN_test_label = np.load(file2_5_label_f)

with open(cluster_fname + 'testfile_le21_flat_weight.npy', 'rb') as test_weight_f:
    test_weight_arr = np.load(test_weight_f)
test_weight_arr = 25000*test_weight_arr
    
print("DNN_training : ", len(DNN_train_label))
print("DNN_test : ", len(DNN_test_label))


#CNN
cluster_fname = '/home/chengyu/paper/front_jet/root_numpy/array_save/s_cluster/'
track_fname = '/home/chengyu/paper/front_jet/root_numpy/array_save/s_track/'
#input training file
with open(cluster_fname + 'trainfile_le21_flat_distri.npy', 'rb') as cluster_file2_1_intensity_f:
    cluster_file2_1_intensity_arr = np.load(cluster_file2_1_intensity_f)
with open(track_fname + 'trainfile_le21_flat_distri.npy', 'rb') as track_file2_1_intensity_f:
    track_file2_1_intensity_arr = np.load(track_file2_1_intensity_f)
CNN_train_sample = cluster_track_intensity_arr(cluster_file2_1_intensity_arr, track_file2_1_intensity_arr)
#input test file
with open(cluster_fname + 'testfile_le21_flat_distri.npy', 'rb') as cluster_file2_5_intensity_f:
    cluster_file2_5_intensity_arr = np.load(cluster_file2_5_intensity_f)
with open(track_fname + 'testfile_le21_flat_distri.npy', 'rb') as track_file2_5_intensity_f:
    track_file2_5_intensity_arr = np.load(track_file2_5_intensity_f)
CNN_test_sample = cluster_track_intensity_arr(cluster_file2_5_intensity_arr, track_file2_5_intensity_arr)

print("CNN_training : ", len(CNN_train_sample))
print("CNN_test : ", len(CNN_test_sample))

with open(cluster_fname + 'trainfile_le21_flat_weight.npy', 'rb') as weight_f:
    weight_arr = np.load(weight_f)
weight_arr = 25000*weight_arr

print("--------Traning--------")
print("sample size : [DNN=31, CNN=16x16x2]")
print("DNN size : ", len(DNN_train_sample[0]))
print("CNN size : ", len(CNN_train_sample[0]))
history = full_model.fit([DNN_train_sample, CNN_train_sample], DNN_train_label, epochs=100, validation_data=([DNN_test_sample, CNN_test_sample], DNN_test_label, test_weight_arr),  sample_weight=weight_arr, callbacks=[callback])
print()
fig = show_history(history)  #show history function
plt.savefig('pTbin/plot/DNN_CNN_sjet_trainfile_le21_flat_rate1_BDTinput_revised.png')
full_model.save('pTbin/model/DNN_CNN_model_sjet_trainfile_le21_flat_rate1_BDTinput_revised.h5')
#print('--------history-----------')
#print('history array : ', history)
print("epochs: ", len(history.history['loss']))

#print("\n-------save npy----------")
#probability_model = tf.keras.Sequential([
 #   full_model,
  #  tf.keras.layers.Softmax()
#])
#prob = full_model.predict([DNN_test_sample, CNN_test_sample], batch_size=100)
#pro_arr = tf.nn.softmax(prob).numpy()
#print(DNN_test_label)
#print(weight_arr)
#print(pro_arr)
#pro_arr = probability_model([DNN_test_sample, CNN_test_sample])

#with open('output/DNN_CNN_prob_sjet_trainfile_le21_flat_weight_31_nor_64_try60.npy', 'wb') as pro_f:
 #   np.save(pro_f, pro_arr)

#with open('output/DNN_CNN_label_sjet_trainfile_le21_flat_weight_31_nor_64_try60.npy', 'wb') as label_f:
 #   np.save(label_f, DNN_test_label)

print("rate : ", 0.00001)

print("\n------successful------")

