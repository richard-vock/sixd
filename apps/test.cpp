#include <iostream>
#include <sixd.hpp>

int main(int , char **)
{
    std::string root("/data/sixd/hinterstoisser/train");
    sixd::dataset dataset(root);

    for (auto const& obj : dataset.samples()) {
        std::cout << obj.first << " (" << obj.second.size() << " image)\n";
        for (auto const& s : obj.second) {
            auto depth_img = s.load_depth_map(root);
        }
    }
    return 0;
}
