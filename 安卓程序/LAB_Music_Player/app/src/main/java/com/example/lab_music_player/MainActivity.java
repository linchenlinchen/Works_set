package com.example.lab_music_player;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";/*由logt+TAB自动生成。*/
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu,menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()){
            case R.id.item1:
                Toast.makeText(this,"You clicked item1",Toast.LENGTH_LONG).show();
                break;
            case R.id.item2:
                Toast.makeText(this,"You clicked item2",Toast.LENGTH_LONG).show();
                break;
                default:break;
        }
        return true;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button button = (Button)findViewById(R.id.bt);
        /*隐藏默认导航栏*/
        ActionBar actionBar = getSupportActionBar();
        if(actionBar != null){
            actionBar.hide();
        }
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
//                Intent intent = new Intent("android.intent.action.FROM_MAIN");/*默认这里还有个category为android.intent.category.DEFAULT的要求，如果Manifest忘记了可会崩溃*/
//                intent.addCategory("android.intent.category.ALTERNATIVE");
                /*打开网页*/
                    Intent intent = new Intent(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("http://www.baidu.com"));
                startActivity(intent);
            }
        });
        List<Fruit> list = new ArrayList<>();

        for (int i = 0; i < 2; i++) {
            list.add(new Fruit("apple",R.drawable.apple_pic));
            list.add(new Fruit("banana",R.drawable.banana_pic));
            list.add(new Fruit("cherry",R.drawable.cherry_pic));
            list.add(new Fruit("grape",R.drawable.grape_pic));
            list.add(new Fruit("mango",R.drawable.mango_pic));
            list.add(new Fruit("orange",R.drawable.orange_pic));
            list.add(new Fruit("pear",R.drawable.pear_pic));
            list.add(new Fruit("pineapple",R.drawable.pineapple_pic));
            list.add(new Fruit("strawberry",R.drawable.strawberry_pic));
            list.add(new Fruit("watermelon",R.drawable.watermelon_pic));
        }
        RecyclerView rlistView = (RecyclerView) findViewById(R.id.rlst);
        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(this);
        linearLayoutManager.setOrientation(LinearLayoutManager.HORIZONTAL);
        rlistView.setLayoutManager(linearLayoutManager);
        FruitAdapter arrayAdapter = new FruitAdapter(list);
        rlistView.setAdapter(arrayAdapter);


    }
}
