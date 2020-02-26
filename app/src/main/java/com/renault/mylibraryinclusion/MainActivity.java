package com.renault.mylibraryinclusion;


import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Camera;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.os.Bundle;
import android.view.TextureView;
import android.view.View;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("my-lib");
    }

    int i = 1;
    int angle = 90;
    Bitmap bitmap = null;
    String dest = null;

    TextureView textureView;

    CameraManager cameraManager;
    CameraCaptureSession cameraCaptureSession;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        dest = this.getCacheDir().getAbsolutePath() + "/canny.JPG";

        try{
//            InputStream is = this.getAssets().open("img.JPG");
            InputStream is = this.getAssets().open("1280_ref_computed.png");
            bitmap = BitmapFactory.decodeStream(is);
        } catch (Exception e){
            e.printStackTrace();
        }


        textureView = this.findViewById(R.id.textureView);

    }

    public void rotatePicAction(View view){
        Toast.makeText(this, sayHello(i++), Toast.LENGTH_SHORT).show();
        this.rotatePic(bitmap, dest, angle);
        angle += 90;
        Canvas canvas = textureView.lockCanvas();
        canvas.drawBitmap(BitmapFactory.decodeFile(dest), new Matrix(), new Paint());
        textureView.unlockCanvasAndPost(canvas);

    }

    public void doCanny(View view){

        this.canny(bitmap, dest);
        Canvas canvas = textureView.lockCanvas();
        canvas.drawBitmap(BitmapFactory.decodeFile(dest), new Matrix(), new Paint());
        textureView.unlockCanvasAndPost(canvas);
    }

    public void drawChessboardAction(View view){
        this.drawChessboard(bitmap, dest);
        Canvas canvas = textureView.lockCanvas();
        canvas.drawBitmap(BitmapFactory.decodeFile(dest), new Matrix(), new Paint());
        textureView.unlockCanvasAndPost(canvas);
    }

    public final native void canny(Bitmap var1, String var2);
    public final native void rotatePic(Bitmap var1, String var2, int angle);
    public final native String sayHello(int i);
    public final native void drawChessboard(Bitmap var1, String var2);

}
