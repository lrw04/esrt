#include "scripting.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "camera.h"
#include "material.h"
#include "render.h"
#include "scene.h"

// v: vertex
// m: material
// t: texture
// o: object
// c: camera
// r: render

std::map<std::string, std::string> read_kv(std::istream& st) {
    std::string k;
    std::map<std::string, std::string> res;
    while (st >> k) {
        if (k == "e") break;
        std::string v;
        st >> v;
        res[k] = v;
    }
    return res;
}

template <typename T>
T cyclic_access(const std::vector<T>& v, int index) {
    return index >= 0 ? v[index] : v[index + v.size()];
}

// TODO: error handling
bool execute_script(std::istream& st) {
    std::string t;
    std::vector<v3> vectors;
    std::vector<std::shared_ptr<material>> materials;
    std::vector<std::shared_ptr<texture>> textures;
    std::vector<std::shared_ptr<object>> objects;
    std::vector<camera> cameras;
    while (st >> t) {
        if (t == "e") break;
        if (t == "v") {
            real x, y, z;
            st >> x >> y >> z;
            vectors.emplace_back(x, y, z);
            continue;
        }
        if (t == "m") {
            st >> t;
            auto param = read_kv(st);
            if (t == "lambertian") {
                materials.push_back(std::make_shared<lambertian>(
                    cyclic_access(textures, std::stoi(param["albedo"]))));
            } else if (t == "diffuse-light") {
                materials.push_back(std::make_shared<diffuse_light>(
                    cyclic_access(textures, std::stoi(param["emission"]))));
            } else if (t == "reflective") {
                materials.push_back(std::make_shared<reflective>(
                    cyclic_access(textures, std::stoi(param["albedo"])),
                    (real)std::stold(param["fuzz"])));
            } else {
                return false;
            }
            continue;
        }
        if (t == "t") {
            st >> t;
            auto param = read_kv(st);
            if (t == "solid-color") {
                textures.push_back(std::make_shared<solid_color>(
                    cyclic_access(vectors, std::stoi(param["color"]))));
            } else {
                return false;
            }
            continue;
        }
        if (t == "o") {
            st >> t;
            if (t == "triangle") {
                int a, b, c, m;
                st >> a >> b >> c >> m;
                objects.push_back(std::make_shared<triangle>(
                    cyclic_access(vectors, a), cyclic_access(vectors, b),
                    cyclic_access(vectors, c), cyclic_access(materials, m)));
            } else if (t == "sphere") {
                int o;
                real r;
                int m;
                st >> o >> r >> m;
                objects.push_back(std::make_shared<sphere>(
                    cyclic_access(vectors, o), r, cyclic_access(materials, m)));
            } else if (t == "union") {
                std::vector<std::shared_ptr<object>> children;
                std::string k;
                while (st >> k) {
                    if (k == "e") break;
                    auto pos = k.find('~');
                    if (pos != std::string::npos) {
                        auto from = std::stoll(k.substr(0, pos));
                        auto to = std::stoll(k.substr(pos + 1));
                        for (auto i = from; i <= to; i++)
                            children.push_back(cyclic_access(objects, i));
                    } else {
                        children.push_back(
                            cyclic_access(objects, std::stoi(k)));
                    }
                }
                objects.push_back(std::make_shared<bvh>(children));
            } else {
                return false;
            }
            continue;
        }
        if (t == "c") {
            auto param = read_kv(st);
            auto ar_s = param["aspect-ratio"];
            auto pos = ar_s.find('/');
            real ar = 0;
            if (pos == std::string::npos) {
                ar = (real)std::stold(ar_s);
            } else {
                real numerator = (real)std::stold(ar_s.substr(0, pos));
                real denominator = (real)std::stold(ar_s.substr(pos + 1));
                ar = numerator / denominator;
            }

            auto fov_s = param["fov"];
            real fov = (real)(fov_s[fov_s.length() - 1] == 'd'
                                  ? std::stold(fov_s) / 180 * pi
                                  : std::stold(fov_s));

            cameras.emplace_back(
                cyclic_access(vectors, std::stoi(param["origin"])),
                cyclic_access(vectors, std::stoi(param["up"])),
                cyclic_access(vectors, std::stoi(param["direction"])), ar, fov);
            continue;
        }
        if (t == "r") {
            auto param = read_kv(st);
            std::shared_ptr<object> obj =
                cyclic_access(objects, std::stoi(param["object"]));
            camera cam = cyclic_access(cameras, std::stoi(param["camera"]));
            std::size_t w = std::stoull(param["width"]);
            unsigned samples = std::stoul(param["samples"]);
            unsigned max_depth = std::stoul(param["max-depth"]);
            real gamma = (real)std::stold(param["gamma"]);
            std::cerr << "Rendering " << param["png-out"] << ":\n";

            auto im = render(obj, cam, w, samples, max_depth, gamma);
            im.write_png(param["png-out"]);
            continue;
        }
        if (t == "#") {
            st >> t;
            continue;
        }
        return false;
    }
    return true;
}
