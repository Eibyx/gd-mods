#include "BaseSetting.hpp"

class TextSetting : public BaseSetting {

private:

    void init(float) override;

    SETTING_CTOR_CREATE(TextSetting, BaseSetting)

};
