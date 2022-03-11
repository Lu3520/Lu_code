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

#input training file

cluster_fname = 'path'
track_fname = 'path'

#train_sample
with open(cluster_fname + 'trainfile.npy', 'rb') as cluster_trainfile_distri_f:
    cluster_conv1d_train_sample = np.load(cluster_trainfile_distri_f)

with open(track_fname + 'trainfile.npy', 'rb') as track_trainfile_distri_f:
    track_conv1d_train_sample = np.load(track_trainfile_distri_f)

    
with open(cluster_fname + 'trainfile__label.npy', 'rb') as trainfile_label_f:
    conv1d_train_label = np.load(trainfile_label_f)

quark_label = 0
gluon_label = 0
for i in range(len(conv1d_train_label)):
    if conv1d_train_label[i] == 0: quark_label = quark_label + 1
    if conv1d_train_label[i] == 1: gluon_label = gluon_label + 1

regularization_Lambda = 0.00000001
#model
track_input = tf.keras.layers.Input(shape=(140 ,3))
track_mask = tf.keras.layers.Masking().compute_mask(track_input)
track_mask = tf.keras.layers.Lambda(lambda x: tf.expand_dims(tf.cast(x, "float32"), -1))(track_mask)
#x = tf.keras.layers.Conv1D(32, 1, activation='relu')(track_input)
#x = tf.keras.layers.Conv1D(32, 1, activation='relu')(x)
#x = tf.keras.layers.Conv1D(32, 1, activation=None)(x)
x = tf.keras.layers.Conv1D(64, 1, activation='relu')(track_input)
x = tf.keras.layers.Conv1D(64, 1, activation='relu')(x)
x = tf.keras.layers.Conv1D(64, 1, activation=None)(x)
x = tf.keras.layers.Multiply()([x, track_mask])
x = tf.keras.layers.Lambda(lambda x: tf.math.reduce_sum(x, axis=1))(x)
#change from 128 to 64
x = tf.keras.layers.Dense(128, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(x)
x = tf.keras.layers.Dropout(0.3)(x)
x = tf.keras.layers.Dense(128, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(x)
track_output = tf.keras.layers.Dropout(0.3)(x)
#track_output = tf.keras.layers.Dense(2)(x)


cluster_input = tf.keras.layers.Input(shape=(70 ,3))
cluster_mask = tf.keras.layers.Masking().compute_mask(cluster_input)
cluster_mask = tf.keras.layers.Lambda(lambda x: tf.expand_dims(tf.cast(x, "float32"), -1))(cluster_mask)
#change from 32 to 64
x = tf.keras.layers.Conv1D(32, 1, activation='relu')(cluster_input)
x = tf.keras.layers.Conv1D(32, 1, activation='relu')(x)
x = tf.keras.layers.Conv1D(32, 1, activation=None)(x)
x = tf.keras.layers.Multiply()([x, cluster_mask])
x = tf.keras.layers.Lambda(lambda x: tf.math.reduce_sum(x, axis=1))(x)
#change from 64 to 128
x = tf.keras.layers.Dense(64, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(x)
x = tf.keras.layers.Dropout(0.3)(x)
x = tf.keras.layers.Dense(64, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(x)
cluster_output = tf.keras.layers.Dropout(0.3)(x)
#cluster_output = tf.keras.layers.Dense(2)(x)


##DNN
#model
input_DNN = tf.keras.layers.Input(shape=(None, 31))
mask = tf.keras.layers.Masking().compute_mask(input_DNN)
mask = tf.keras.layers.Lambda(lambda x: tf.expand_dims(tf.cast(x, "float32"), -1))(mask)
x = tf.keras.layers.Conv1D(16, 1, activation='relu')(input_DNN)
x = tf.keras.layers.Conv1D(16, 1, activation='relu')(x)
x = tf.keras.layers.Conv1D(16, 1, activation=None)(x)
x = tf.keras.layers.Multiply()([x, mask])
x = tf.keras.layers.Lambda(lambda x: tf.math.reduce_sum(x, axis=1))(x)
x = tf.keras.layers.Dense(64, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(x)
x = tf.keras.layers.Dropout(0.3)(x)
x = tf.keras.layers.Dense(64, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda))(x)
DNN_output = tf.keras.layers.Dropout(0.3)(x)


# Concatenate
concat = tf.keras.layers.Concatenate()([cluster_output, track_output, DNN_output])
# output 192 to 256
front = tf.keras.layers.Dense(192)(concat)
output = tf.keras.layers.Dense(2)(front)

full_model = tf.keras.Model(inputs=[cluster_input, track_input, input_DNN], outputs=[output])
full_model.summary()

#loss function
rate = 0.00001
loss_fn = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True)
#optimizer
opt = keras.optimizers.Adam(learning_rate=rate)

full_model.compile(optimizer=opt,
              loss=loss_fn,
              metrics=['accuracy'])

#callback
callback = tf.keras.callbacks.EarlyStopping(monitor='val_loss', patience=20)

with open(cluster_fname + 'trainfile_weight.npy', 'rb') as weight_f:
    conv1d_weight_arr = np.load(weight_f)

#input test sample
with open(cluster_fname + 'testfile.npy', 'rb') as cluster_testfile_distri_f:
    cluster_conv1d_test_sample = np.load(cluster_testfile_distri_f)
with open(track_fname + 'testfile.npy', 'rb') as track_testfile_distri_f:
    track_conv1d_test_sample = np.load(track_testfile_distri_f)

with open(cluster_fname + 'testfile_label.npy', 'rb') as testfile_label_f:
    conv1d_test_label = np.load(testfile_label_f)

with open(cluster_fname + 'testfile_weight.npy', 'rb') as test_weight_f:
    conv1d_test_weight_arr = np.load(test_weight_f)

# DNN
#input training file
DNN_fname = 'path'
#train_sample
with open(DNN_fname + 'trainfile.npy', 'rb') as DNN_train_scalar_f:
    DNN_train_sample = np.load(DNN_train_scalar_f)

with open(DNN_fname + 'testfile.npy', 'rb') as DNN_test_scalar_f:
    DNN_test_sample = np.load(DNN_test_scalar_f)


DNN_train_sample = tf.reshape(DNN_train_sample, [int(DNN_train_sample.shape[0]), 1, 31])
DNN_test_sample = tf.reshape(DNN_test_sample, [int(DNN_test_sample.shape[0]), 1, 31])


print("--------Traning--------")
print("sample size : 210 x 3")
print("# of Sample : ", len(track_conv1d_train_sample))
history = full_model.fit([cluster_conv1d_train_sample, track_conv1d_train_sample, DNN_train_sample], conv1d_train_label, epochs=90, validation_data=([cluster_conv1d_test_sample, track_conv1d_test_sample, DNN_test_sample], conv1d_test_label, conv1d_test_weight_arr), sample_weight=conv1d_weight_arr, callbacks=[callback])
history = model.fit(train_sample, train_label, epochs=100, validation_data=(test_sample, test_label))
fig = show_history(history)  #show history function
full_model.save('pTbin/model/conv1d_all_gt21_flat_less_rate1_new.h5')

print("\n---------Evaluate--------")

print("regularization_Lambda: ", regularization_Lambda)
print("learing rate: ", rate)


print("\n------successful------")
