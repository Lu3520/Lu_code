import numpy as np
import tensorflow as tf
from tensorflow.keras import datasets, layers, models
import matplotlib.pyplot as plt
from tensorflow import keras
import matplotlib
matplotlib.use('Agg')
#ioff()

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
        for row in range(0,15):
            for col in range(0,15):
                    output_arr[i][row][col][0] = cluster_arr[i][row][col]
                    output_arr[i][row][col][1] = track_arr[i][row][col]
    return output_arr

def label_trans(arr):
    arr_len = len(arr)
    output_arr = np.zeros((arr_len), dtype=float).reshape(arr_len,1)
    for i in range(0, arr_len):
        output_arr[i][0] = arr[i]
    return output_arr

#input training file

cluster_fname = '/home/chengyu/paper/front_jet/root_numpy/array_save/s_cluster/'
track_fname = '/home/chengyu/paper/front_jet/root_numpy/array_save/s_track/'



regularization_Lambda = 0.00000001
rate = 0.00001
#model
model = models.Sequential()
model.add(layers.Conv2D(256, (7, 7), activation='relu', input_shape=(16, 16, 2), kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda)))
model.add(layers.Dropout(0.3))
#model.add(layers.MaxPooling2D((2, 2)))
#origin
model.add(layers.Conv2D(128, (5, 5), activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda)))

#model.add(layers.Conv2D(128, (4, 4), activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda)))

model.add(layers.Dropout(0.3))
#model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Conv2D(64, (3, 3), activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda)))
model.add(layers.Dropout(0.3))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Flatten())
#origin = 128
model.add(layers.Dense(64, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda)))
model.add(layers.Dropout(0.3))
model.add(layers.Dense(64, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda)))
model.add(layers.Dropout(0.3))
#model.add(layers.Dense(32, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda)))
#model.add(layers.Dropout(0.3))
model.add(layers.Dense(2))
model.summary()

#loss function
#loss_fn = tf.keras.losses.CategoricalCrossentropy(from_logits=True)
loss_fn = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True)
#optimizer
opt = keras.optimizers.Adam(learning_rate=rate)

with open(cluster_fname + 'trainfile_le21_flat_small_100k_weight.npy', 'rb') as weight_f:
    weight_arr = np.load(weight_f)

weight_arr = 25000*weight_arr

model.compile(optimizer=opt,
              loss=loss_fn,
              metrics=['accuracy'])


#with open(cluster_fname + 'trainfile_le21_flat_distri.npy', 'rb') as cluster_trainfile_le21_intensity_f:
 #   cluster_trainfile_le21_intensity_arr = np.load(cluster_trainfile_le21_intensity_f)
#train_sample
with open(cluster_fname + 'trainfile_le21_flat_small_100k_distri.npy', 'rb') as cluster_trainfile_le21_intensity_f:
    cluster_trainfile_le21_intensity_arr = np.load(cluster_trainfile_le21_intensity_f)
with open(track_fname + 'trainfile_le21_flat_small_100k_distri.npy', 'rb') as track_trainfile_le21_intensity_f:
    track_trainfile_le21_intensity_arr = np.load(track_trainfile_le21_intensity_f)
train_sample = cluster_track_intensity_arr(cluster_trainfile_le21_intensity_arr, track_trainfile_le21_intensity_arr)
    
with open(cluster_fname + 'trainfile_le21_flat_small_100k_label.npy', 'rb') as cluster_trainfile_le21_label_f:
    cluster_trainfile_le21_label_arr = np.load(cluster_trainfile_le21_label_f)
#train_label = label_trans(cluster_trainfile_le21_label_arr)
train_label = cluster_trainfile_le21_label_arr


print("cluster_track_trainfile_le21_arr : ", len(train_sample))
print("trainfile_le21_label : ", len(train_label))



#input test sample
with open(cluster_fname + 'testfile_le21_flat_small_50k_distri.npy', 'rb') as cluster_testfile_le21_intensity_f:
    cluster_testfile_le21_intensity_arr = np.load(cluster_testfile_le21_intensity_f)
with open(track_fname + 'testfile_le21_flat_small_50k_distri.npy', 'rb') as track_testfile_le21_intensity_f:
    track_testfile_le21_intensity_arr = np.load(track_testfile_le21_intensity_f)
test_sample = cluster_track_intensity_arr(cluster_testfile_le21_intensity_arr, track_testfile_le21_intensity_arr)
    
with open(cluster_fname + 'testfile_le21_flat_small_50k_label.npy', 'rb') as cluster_testfile_le21_label_f:
    cluster_testfile_le21_label_arr = np.load(cluster_testfile_le21_label_f)
#test_label = label_trans(cluster_testfile_le21_label_arr)
test_label = cluster_testfile_le21_label_arr

with open(cluster_fname + 'testfile_le21_flat_small_50k_weight.npy', 'rb') as test_weight_f:
    test_weight_arr = np.load(test_weight_f)
test_weight_arr = 25000*test_weight_arr

callback = tf.keras.callbacks.EarlyStopping(monitor='val_loss', patience=15)

#print("test label", test_label)

print("--------Traning--------")
print("sample size : 16x16x2")
print("# of Sample : ", len(train_label))
history = model.fit(train_sample, train_label, epochs=70, validation_data=(test_sample, test_label, test_weight_arr), sample_weight=weight_arr, callbacks=[callback])
#history = model.fit(train_sample, train_label, epochs=50,  sample_weight=weight_arr, callbacks=[callback])
#history = model.fit(train_sample, train_label, epochs=20, validation_data=(test_sample, test_label))
print(history)
fig = show_history(history)  #show history function
plt.savefig('pTbin/plot/CNN_2D_training_sjet_train_le21_flat_small_1rate_100k.png')
model.save('pTbin/model/CNN_2D_model_sjet_train_le21_flat_small_1rate_100k.h5')


#print("test_sampe : ", len(test_sample))
#print("test_label : ", len(test_label))

#print("\n---------Evaluate--------")
#model.evaluate(test_sample,  test_label, verbose=2)

print("\n-------save npy----------")

#print(test_label)
print(weight_arr)
#pro_arr = tf.nn.softmax(model(test_sample, batch_size=100))
pro_arr = model.predict(test_sample, batch_size=100)
pro_arr = tf.nn.softmax(pro_arr).numpy()
print(pro_arr)


#with open('output/CNN_2D_prob_sjet_train_le21_flat_weight_40times.npy', 'wb') as pro_f:
 #   np.save(pro_f, pro_arr)

#with open('output/CNN_2D_label_sjet_train_le21_flat_weight_40times.npy', 'wb') as label_f:
 #   np.save(label_f, test_label)

#print("layer weight: ", model.layers[-1].weights)


print("regularization_Lambda: ", regularization_Lambda)
print("learning rate: ", rate)

print("\n------successful------")
