#include <sixd.hpp>

#include <map>
#include <filesystem>
namespace fs = std::filesystem;
#include <fstream>

#include <yaml-cpp/yaml.h>

namespace sixd
{

png::image<png::gray_pixel_16>
sample::load_depth_map(std::string_view root) const {
    fs::path p(root);
    p /= obj;
    char k[5];
    sprintf(k, "%04u", static_cast<unsigned int>(std::stol(key)));
    p /= std::string("depth/") + k + ".png";
    return png::image<png::gray_pixel_16>(p.string());
}

png::image<png::rgb_pixel>
sample::load_rgb_map(std::string_view root) const {
    fs::path p(root);
    p /= obj;
    char k[5];
    sprintf(k, "%04u", static_cast<unsigned int>(std::stol(key)));
    p /= std::string("rgb/") + k + ".png";
    return png::image<png::rgb_pixel>(p.string());
}

struct dataset::impl {
    impl(std::string_view&& root) : root(root) {
        load_root();
    }

    void
    load_root() {
        fs::directory_iterator dir_it(root), end_it;
        for (; dir_it != end_it; ++dir_it) {
            if (!fs::is_directory(*dir_it)) {
                continue;
            }

            fs::path obj = dir_it->path().filename();
            fs::path meta_path = root / obj / "info.yml";
            if (!fs::exists(meta_path)) {
                continue;
            }

            samples[obj.string()] = std::vector<sample>{};
            YAML::Node doc = YAML::LoadFile(meta_path.string());
            for (auto it = doc.begin(); it != doc.end(); ++it) {
                std::vector cam_k = it->second["cam_K"].as<std::vector<float>>();

                samples[obj.string()].push_back(sample{
                    it->first.as<std::string>(),
                    obj.string(),
                    Eigen::Map<Eigen::Matrix<float, 3, 3, Eigen::RowMajor>>(cam_k.data()),
                    it->second["depth_scale"].as<float>(),
                    it->second["view_level"].as<int>()
                });
            }
        }
    }

    std::filesystem::path root;
    std::map<std::string, std::vector<sample>> samples;
};

void
dataset::impl_deleter::operator()(dataset::impl* ptr) const { delete ptr; }

dataset::dataset(std::string_view root) : impl_(new impl(std::move(root))) {
}

std::map<std::string, std::vector<sample>> const&
dataset::samples() const {
    return impl_->samples;
}

std::map<std::string, std::vector<sample>> &
dataset::samples() {
    return impl_->samples;
}

} /* sixd */
