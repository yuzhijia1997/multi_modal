INCLUDEPATH += \
    "D:\libtorch_debug\include"\
    "D:\libtorch_debug\include\torch\csrc\api\include"


LIBS += -L"D:\libtorch_debug\lib" \
        -lasmjit \
        -lc10 \
        -lc10_cuda \
        -lc10d \
        -lcaffe2_detectron_ops_gpu \
        -lcaffe2_module_test_dynamic \
        -lcaffe2_nvrtc \
        -lclog \
        -lcpuinfo \
        -ldnnl \
        -lfbgemm \
        -lgloo \
        -lgloo_cuda \
#        -llibprotobufd \
#        -llibprotobuf-lited \
        -llibprotocd \
        -lmkldnn \
        -ltorch \
        -ltorch_cpu \
        -ltorch_cuda
