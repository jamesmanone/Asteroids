"use strict";

(function() {
  this.cnv = document.getElementById("cnv");
  this.ctx = cnv.getContext("2d");
  this.h = window.innerHeight > 720 ? 720 : window.innerHeight;
  // this.h = 576;
  this.w = (this.h/9)*16;
  this.bytes = this.w*this.h*4;
  this.title = fps => `Never Tell Me the Odds ${fps.toFixed(2)} fps`;
  this.frames = 0;
  this.geom = 0;

  cnv.width = this.w;
  cnv.height = this.h;


  this.loop = () => {
    if(!this.geom) this.renderer.randomFrame();
    else this.renderer.geometryTestFrame();
    const ptr = this.renderer.getFrame();
    const px = new Uint8ClampedArray(Module.HEAPU8.buffer, ptr, this.bytes);

    this.ctx.putImageData(new ImageData(px, this.w), 0, 0);
    ++this.frames;

    if(performance.now() - this.last > 3000) {
      this.geom = ~this.geom;
      const fps = this.frames / ((performance.now() - this.last) / 1000);
      this.frames = 0;
      this.last = performance.now();
      document.title = this.title(fps);
    }

    requestAnimationFrame(this.loop);
  }

  this.setup = () => {
    if(!(Module && Module.Renderer && Module.Renderer.constructor)) return setTimeout(this.setup, 500);
    this.renderer = new Module.Renderer(this.w, this.h);
    this.last = performance.now()
    requestAnimationFrame(this.loop);
  }

  this.setup();
}).bind({})();


