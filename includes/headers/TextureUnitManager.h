#pragma once
class TextureUnitManager {
public:
    static int get_next_unit() {
        static int current_unit = 0; 
        return current_unit++;
    }
};