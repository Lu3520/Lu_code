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

input_fname = 'output/arrayfile/'

#train_sample
with open(input_fname + 'trainfile.npy', 'rb') as trainfile_scalar_f:
    train_sample = np.load(trainfile_scalar_f)
    
with open(input_fname + 'trainfile_label.npy', 'rb') as trainfile_label_f:
    train_label = np.load(trainfile_label_f)


quark_label = 0
gluon_label = 0
for i in range(len(train_label)):
    if train_label[i] == 0: quark_label = quark_label + 1
    if train_label[i] == 1: gluon_label = gluon_label + 1



regularization_Lambda = 0.00000001
#model
model = models.Sequential()
model.add(tf.keras.Input(shape=(31,)))
model.add(layers.Dense(64, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda)))
model.add(layers.Dropout(0.3))
model.add(layers.Dense(64, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(l=regularization_Lambda)))
model.add(layers.Dropout(0.3))
model.add(layers.Dense(2))
model.summary()

#loss function
rate = 0.00001
loss_fn = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True)
#optimizer
opt = keras.optimizers.Adam(learning_rate=rate)

callback = tf.keras.callbacks.EarlyStopping(monitor='val_loss', patience=15)

model.compile(optimizer=opt,
              loss=loss_fn,
              metrics=['accuracy'])

cluster_fname = '/home/chengyu/paper/front_jet/conv1d/arrayfile/cluster/'

with open(cluster_fname + 'trainfile_le21_le100_weight.npy', 'rb') as weight_f:
    weight_arr = np.load(weight_f)


#input test sample
with open(input_fname + 'testfile_le21_le100_scalar.npy', 'rb') as testfile_scalar_f:
    test_sample = np.load(testfile_scalar_f)

with open(input_fname + 'testfile_le21_le100_label.npy', 'rb') as testfile_label_f:
    test_label = np.load(testfile_label_f)

with open(cluster_fname + 'testfile_le21_le100_weight.npy', 'rb') as test_weight_f:
    test_weight_arr = np.load(test_weight_f)


print("--------Traning--------")
print("sample size : 31")
print("# of Sample : ", len(train_sample))
history = model.fit(train_sample, train_label, epochs=100, validation_data=(test_sample, test_label, test_weight_arr), sample_weight=weight_arr, callbacks=[callback])
fig = show_history(history)  #show history function

print("\n---------Evaluate--------")

model.evaluate(test_sample,  test_label, verbose=2)

print("\n-------save npy----------")

print(test_label)
print(weight_arr)
pro_arr = model.predict(test_sample, batch_size=100)
pro_arr = tf.nn.softmax(pro_arr).numpy()
print(pro_arr)

with open('prob_array/DNN_2layer_prob_sjet_train_le21_31_weight_nor_64_try.npy', 'wb') as pro_f:
    np.save(pro_f, pro_arr)

with open('prob_array/DNN_2layer_label_sjet_train_le21_31_weight_nor_64_try.npy', 'wb') as label_f:
    np.save(label_f, test_label)

print("regularization_Lambda: ", regularization_Lambda)
print("learing rate: ", rate)


print("\n------successful------")
