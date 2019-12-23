#pragma once

#include <map>
#include <memory>
#include <string_view>

#include <Eigen/Dense>
#include <png++/png.hpp>

namespace sixd {

struct sample {
    std::string key;
    std::string obj;
    Eigen::Matrix3f cam_k;
    float depth_scale;
    int view_level;

    png::image<png::gray_pixel_16>
    load_depth_map(std::string_view root) const;

    png::image<png::rgb_pixel>
    load_rgb_map(std::string_view root) const;
};

class dataset {
public:
    dataset(std::string_view root);

    std::map<std::string, std::vector<sample>> const&
    samples() const;

    std::map<std::string, std::vector<sample>> &
    samples();

private:
    struct impl;
    struct impl_deleter { void operator()(impl*) const; };
    std::unique_ptr<impl, impl_deleter> impl_;
};

}
