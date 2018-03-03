package somebody.ndkxperiment;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class RendererWrapper implements GLSurfaceView.Renderer {

    // Used to load the 'native-renderer' library on application startup.
    static {
        System.loadLibrary("native-renderer");
    }

    @Override
    public void onSurfaceCreated(GL10 unused, EGLConfig config) {
        onSurfaceCreatedNative();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        onSurfaceChangedNative(width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        onDrawFrameNative();
    }

    public native void onSurfaceCreatedNative();
    public native void onSurfaceChangedNative(int width, int height);
    public native void onDrawFrameNative();
}