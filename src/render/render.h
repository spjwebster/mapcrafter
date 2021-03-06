/*
 * Copyright 2012, 2013 Moritz Hilscher
 *
 * This file is part of mapcrafter.
 *
 * mapcrafter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mapcrafter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mapcrafter.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RENDER_H_
#define RENDER_H_

#include "mc/pos.h"
#include "mc/cache.h"

#include "render/image.h"
#include "render/textures.h"
#include "render/tile.h"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace mapcrafter {
namespace render {

/**
 * Iterates over the top blocks of a tile.
 */
class TileTopBlockIterator {
private:
	int block_size, tile_size;

	bool is_end;
	int min_row, max_row;
	int min_col, max_col;
	mc::BlockPos top;
public:
	TileTopBlockIterator(const TilePos& tile, int block_size, int tile_size);
	~TileTopBlockIterator();

	void next();
	bool end() const;

	mc::BlockPos current;
	int draw_x, draw_y;
};

/**
 * Iterates over the blocks, which are on a tile on the same position,
 * this means every block is (x+1, z-1 and y-1) of the last block
 */
class BlockRowIterator {
public:
	BlockRowIterator(const mc::BlockPos& block);
	~BlockRowIterator();

	void next();
	bool end() const;

	mc::BlockPos current;
};

/**
 * A combination of id/data.
 */
struct Block {
	Block(uint16_t id = 0, uint16_t data = 0);

	uint16_t id, data;
};

/**
 * A block, which should get drawed on a tile.
 */
struct RenderBlock {

	// drawing position in pixels on the tile
	int x, y;
	bool transparent;
	Image image;
	mc::BlockPos pos;
	uint8_t id, data;

	bool operator<(const RenderBlock& other) const;
};

/**
 * Renders tiles from world data.
 */
class TileRenderer {
private:
	mc::WorldCache& world;
	const BlockImages& images;

	bool render_biomes;

	Block getBlock(const mc::BlockPos& pos, mc::Chunk* chunk) const;
	Biome getBiome(const mc::BlockPos& pos, const mc::Chunk* chunk) const;

	uint16_t checkNeighbors(const mc::BlockPos& pos, mc::Chunk* chunk, uint16_t id,
			uint16_t data) const;
public:
	TileRenderer(mc::WorldCache& world, const BlockImages& textures, bool render_biomes);
	~TileRenderer();

	void renderTile(const TilePos& pos, Image& tile) const;
};

}
}

#endif /* RENDER_H_ */
