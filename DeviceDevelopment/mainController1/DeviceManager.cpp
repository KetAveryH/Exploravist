

class DeviceManager{
    public:
    DeviceManager() : takePic(false), cancelPic(true) {}

    void checkInput() {
        if (touchRead(T14) > 70000) {
            takePic = true;
        }
    }

    void 

    private:
        bool takePic;
        bool cancelPic;
}