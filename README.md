- Do EPOCH = 5000 nên chương trình chạy khá lâu, phải mất tầm 1 - 2p mới chạy xong
- Nếu muốn chương trình chạy nhanh hơn thì giảm EPOCH xuống, tuy nhiên sẽ làm giảm độ chính xác'
- Sau khi chạy chương trình thì console sẽ hiển thị như bên dưới


=== Run information ===

Scheme:       CustomNeuralNetwork -L 0.0100 -N 5000 -H 20
Relation:     BostonHousing
Instances:    506
Attributes:   14
              crim
              zn
              indus
              chas
              nox
              rm
              age
              dis
              rad
              tax
              ptratio
              b
              lstat
              medv
Test mode:    10-fold cross-validation

=== Classifier model (full training set) ===

Linear Node 0
    Inputs    Weights
    Threshold    0.8044
    Node 1    0.3394
    Node 2    0.3461
    Node 3    -1.7637
    Node 4    -0.0081
    Node 5    2.5596
    Node 6    0.0146
    Node 7    -0.3958
    Node 8    -0.0032
    Node 9    0.8598
    Node 10    0.1945
    Node 11    -0.5204
    Node 12    -0.7532
    Node 13    -0.6242
    Node 14    -0.0094
    Node 15    -0.5089
    Node 16    0.5865
    Node 17    -1.5790
    Node 18    -0.4069
    Node 19    2.4020
    Node 20    -0.0103
ReLU Node 1
    Inputs    Weights
    Threshold    0.1137
    Attrib       crim    -0.0622
    Attrib         zn    0.0856
    Attrib      indus    -0.1197
    Attrib       chas    0.0392
    Attrib        nox    -0.0259
    Attrib         rm    0.0014
    Attrib        age    0.0496
    Attrib        dis    -0.1009
    Attrib        rad    0.0900
    Attrib        tax    0.0752
    Attrib    ptratio    0.0807
    Attrib          b    0.1497
    Attrib      lstat    -0.2360
ReLU Node 2
    Inputs    Weights
    Threshold    0.1099
    Attrib       crim    -0.0674
    Attrib         zn    0.0624
    Attrib      indus    -0.1114
    Attrib       chas    0.0479
    Attrib        nox    -0.0122
    Attrib         rm    -0.0115
    Attrib        age    0.0863
    Attrib        dis    -0.1014
    Attrib        rad    0.0823
    Attrib        tax    0.0546
    Attrib    ptratio    0.0856
    Attrib          b    0.1221
    Attrib      lstat    -0.2691
ReLU Node 3
    Inputs    Weights
    Threshold    0.0770
    Attrib       crim    0.4027
    Attrib         zn    0.0257
    Attrib      indus    0.7800
    Attrib       chas    -0.0822
    Attrib        nox    0.2729
    Attrib         rm    0.2785
    Attrib        age    -0.0078
    Attrib        dis    0.7203
    Attrib        rad    -0.2562
    Attrib        tax    -0.1569
    Attrib    ptratio    -0.0742
    Attrib          b    -0.1389
    Attrib      lstat    1.5861
ReLU Node 4
    Inputs    Weights
    Threshold    -0.0184
    Attrib       crim    0.0007
    Attrib         zn    0.0134
    Attrib      indus    -0.0075
    Attrib       chas    -0.0068
    Attrib        nox    -0.0039
    Attrib         rm    0.0021
    Attrib        age    -0.0083
    Attrib        dis    -0.0026
    Attrib        rad    0.0022
    Attrib        tax    -0.0024
    Attrib    ptratio    -0.0064
    Attrib          b    0.0098
    Attrib      lstat    -0.0064
ReLU Node 5
    Inputs    Weights
    Threshold    -0.6356
    Attrib       crim    -0.0626
    Attrib         zn    0.0304
    Attrib      indus    0.4704
    Attrib       chas    -0.0262
    Attrib        nox    0.2941
    Attrib         rm    2.1435
    Attrib        age    -0.0913
    Attrib        dis    0.3653
    Attrib        rad    -0.0900
    Attrib        tax    -0.3380
    Attrib    ptratio    -0.2043
    Attrib          b    -0.5356
    Attrib      lstat    -0.9744
ReLU Node 6
    Inputs    Weights
    Threshold    -0.0324
    Attrib       crim    0.0170
    Attrib         zn    0.0023
    Attrib      indus    0.0087
    Attrib       chas    -0.0036
    Attrib        nox    0.0081
    Attrib         rm    0.0195
    Attrib        age    -0.0024
    Attrib        dis    0.0070
    Attrib        rad    -0.0087
    Attrib        tax    0.0177
    Attrib    ptratio    0.0169
    Attrib          b    -0.0162
    Attrib      lstat    -0.0111
ReLU Node 7
    Inputs    Weights
    Threshold    0.0313
    Attrib       crim    0.0931
    Attrib         zn    -0.0001
    Attrib      indus    0.1752
    Attrib       chas    -0.0206
    Attrib        nox    0.0670
    Attrib         rm    0.0566
    Attrib        age    -0.0079
    Attrib        dis    0.1759
    Attrib        rad    -0.0478
    Attrib        tax    -0.0176
    Attrib    ptratio    -0.0158
    Attrib          b    -0.0352
    Attrib      lstat    0.3513
ReLU Node 8
    Inputs    Weights
    Threshold    -0.0263
    Attrib       crim    -0.0013
    Attrib         zn    -0.0097
    Attrib      indus    -0.0038
    Attrib       chas    0.0004
    Attrib        nox    -0.0172
    Attrib         rm    -0.0138
    Attrib        age    0.0003
    Attrib        dis    0.0046
    Attrib        rad    0.0221
    Attrib        tax    -0.0008
    Attrib    ptratio    0.0049
    Attrib          b    0.0105
    Attrib      lstat    -0.0081
ReLU Node 9
    Inputs    Weights
    Threshold    0.2998
    Attrib       crim    -0.1872
    Attrib         zn    0.1686
    Attrib      indus    -0.2906
    Attrib       chas    0.1188
    Attrib        nox    -0.0555
    Attrib         rm    0.0067
    Attrib        age    0.1758
    Attrib        dis    -0.2553
    Attrib        rad    0.2133
    Attrib        tax    0.1801
    Attrib    ptratio    0.1726
    Attrib          b    0.3052
    Attrib      lstat    -0.6433
ReLU Node 10
    Inputs    Weights
    Threshold    0.0529
    Attrib       crim    -0.0624
    Attrib         zn    0.0261
    Attrib      indus    -0.0621
    Attrib       chas    0.0179
    Attrib        nox    -0.0030
    Attrib         rm    0.0134
    Attrib        age    0.0367
    Attrib        dis    -0.0617
    Attrib        rad    0.0528
    Attrib        tax    0.0332
    Attrib    ptratio    0.0406
    Attrib          b    0.0802
    Attrib      lstat    -0.1488
ReLU Node 11
    Inputs    Weights
    Threshold    0.0265
    Attrib       crim    0.1200
    Attrib         zn    -0.0024
    Attrib      indus    0.2142
    Attrib       chas    -0.0219
    Attrib        nox    0.0886
    Attrib         rm    0.0965
    Attrib        age    -0.0117
    Attrib        dis    0.2166
    Attrib        rad    -0.0538
    Attrib        tax    -0.0457
    Attrib    ptratio    -0.0111
    Attrib          b    -0.0505
    Attrib      lstat    0.4740
ReLU Node 12
    Inputs    Weights
    Threshold    0.0065
    Attrib       crim    0.0191
    Attrib         zn    0.1395
    Attrib      indus    0.1024
    Attrib       chas    -0.0853
    Attrib        nox    0.1518
    Attrib         rm    -0.1868
    Attrib        age    0.5570
    Attrib        dis    -0.1041
    Attrib        rad    -0.1869
    Attrib        tax    -0.2995
    Attrib    ptratio    -0.2311
    Attrib          b    0.1938
    Attrib      lstat    0.0020
ReLU Node 13
    Inputs    Weights
    Threshold    0.0233
    Attrib       crim    0.1502
    Attrib         zn    0.0060
    Attrib      indus    0.2887
    Attrib       chas    -0.0281
    Attrib        nox    0.0984
    Attrib         rm    0.0994
    Attrib        age    -0.0144
    Attrib        dis    0.2578
    Attrib        rad    -0.0784
    Attrib        tax    -0.0476
    Attrib    ptratio    -0.0329
    Attrib          b    -0.0441
    Attrib      lstat    0.5545
ReLU Node 14
    Inputs    Weights
    Threshold    0.0002
    Attrib       crim    -0.0036
    Attrib         zn    -0.0044
    Attrib      indus    -0.0047
    Attrib       chas    0.0112
    Attrib        nox    0.0070
    Attrib         rm    -0.0149
    Attrib        age    -0.0186
    Attrib        dis    0.0058
    Attrib        rad    0.0076
    Attrib        tax    -0.0024
    Attrib    ptratio    -0.0092
    Attrib          b    0.0043
    Attrib      lstat    -0.0035
ReLU Node 15
    Inputs    Weights
    Threshold    0.0109
    Attrib       crim    0.1227
    Attrib         zn    0.0050
    Attrib      indus    0.2332
    Attrib       chas    -0.0235
    Attrib        nox    0.0786
    Attrib         rm    0.0904
    Attrib        age    -0.0053
    Attrib        dis    0.2013
    Attrib        rad    -0.0961
    Attrib        tax    -0.0482
    Attrib    ptratio    -0.0265
    Attrib          b    -0.0329
    Attrib      lstat    0.4501
ReLU Node 16
    Inputs    Weights
    Threshold    0.2042
    Attrib       crim    -0.1373
    Attrib         zn    0.0952
    Attrib      indus    -0.2045
    Attrib       chas    0.0616
    Attrib        nox    -0.0305
    Attrib         rm    0.0123
    Attrib        age    0.1162
    Attrib        dis    -0.1655
    Attrib        rad    0.1326
    Attrib        tax    0.1189
    Attrib    ptratio    0.1266
    Attrib          b    0.2148
    Attrib      lstat    -0.4445
ReLU Node 17
    Inputs    Weights
    Threshold    -0.1606
    Attrib       crim    -0.2390
    Attrib         zn    -0.0062
    Attrib      indus    0.1441
    Attrib       chas    0.3830
    Attrib        nox    0.5725
    Attrib         rm    0.8639
    Attrib        age    -0.5995
    Attrib        dis    -0.0870
    Attrib        rad    -0.2479
    Attrib        tax    0.0791
    Attrib    ptratio    0.3588
    Attrib          b    -0.7629
    Attrib      lstat    0.2666
ReLU Node 18
    Inputs    Weights
    Threshold    0.0305
    Attrib       crim    0.0928
    Attrib         zn    0.0112
    Attrib      indus    0.1670
    Attrib       chas    -0.0146
    Attrib        nox    0.0634
    Attrib         rm    0.0545
    Attrib        age    0.0117
    Attrib        dis    0.1625
    Attrib        rad    -0.0670
    Attrib        tax    -0.0354
    Attrib    ptratio    -0.0188
    Attrib          b    -0.0434
    Attrib      lstat    0.3747
ReLU Node 19
    Inputs    Weights
    Threshold    -0.1129
    Attrib       crim    0.0639
    Attrib         zn    -0.0894
    Attrib      indus    1.0232
    Attrib       chas    -0.1474
    Attrib        nox    0.0303
    Attrib         rm    0.8707
    Attrib        age    -0.1277
    Attrib        dis    0.3447
    Attrib        rad    -0.2568
    Attrib        tax    -0.7063
    Attrib    ptratio    -0.5696
    Attrib          b    -0.3625
    Attrib      lstat    1.8500
ReLU Node 20
    Inputs    Weights
    Threshold    -0.0048
    Attrib       crim    -0.0013
    Attrib         zn    0.0023
    Attrib      indus    0.0038
    Attrib       chas    -0.0150
    Attrib        nox    -0.0088
    Attrib         rm    -0.0070
    Attrib        age    -0.0016
    Attrib        dis    -0.0144
    Attrib        rad    0.0071
    Attrib        tax    -0.0054
    Attrib    ptratio    0.0055
    Attrib          b    -0.0161
    Attrib      lstat    0.0050
Class
    Input
    Node 0

Time taken to build model: 0.23 seconds

=== Cross-validation ===
=== Summary ===

Correlation coefficient                  0.8425
Mean absolute error                      2.4863
Root mean squared error                  3.6599
Relative absolute error                 37.2198 %
Root relative squared error             39.6808 %
Total Number of Instances              501

--------------------------------
Process exited after 86.09 seconds with return value 0
Press any key to continue . . .
