package com.kosphere.test2;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.AppCompatImageView;
import android.view.View;
import android.widget.Button;

import com.ashokvarma.bottomnavigation.BottomNavigationBar;

import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.ashokvarma.bottomnavigation.BottomNavigationBar;
import com.ashokvarma.bottomnavigation.BottomNavigationItem;


public class index extends AppCompatActivity implements BottomNavigationBar.OnTabSelectedListener{
        private BottomNavigationBar bottomNavigationBar;
        int lastSelectedPosition = 0;
        private String TAG = index.class.getSimpleName();
        private MyFragment mMyFragment;
        private ScanFragment mScanFragment;
        private HomeFragment mHomeFragment;

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.index);

            /**
             * bottomNavigation 设置
             */

            bottomNavigationBar = (BottomNavigationBar) findViewById(R.id.bottom_navigation_bar);

            /** 导航基础设置 包括按钮选中效果 导航栏背景色等 */
            bottomNavigationBar
                    .setTabSelectedListener(this)
                    .setMode(BottomNavigationBar.MODE_FIXED)
                    /**
                     *  setMode() 内的参数有三种模式类型：
                     *  MODE_DEFAULT 自动模式：导航栏Item的个数<=3 用 MODE_FIXED 模式，否则用 MODE_SHIFTING 模式
                     *  MODE_FIXED 固定模式：未选中的Item显示文字，无切换动画效果。
                     *  MODE_SHIFTING 切换模式：未选中的Item不显示文字，选中的显示文字，有切换动画效果。
                     */

                    .setBackgroundStyle(BottomNavigationBar.BACKGROUND_STYLE_STATIC)
                    /**
                     *  setBackgroundStyle() 内的参数有三种样式
                     *  BACKGROUND_STYLE_DEFAULT: 默认样式 如果设置的Mode为MODE_FIXED，将使用BACKGROUND_STYLE_STATIC
                     *                                    如果Mode为MODE_SHIFTING将使用BACKGROUND_STYLE_RIPPLE。
                     *  BACKGROUND_STYLE_STATIC: 静态样式 点击无波纹效果
                     *  BACKGROUND_STYLE_RIPPLE: 波纹样式 点击有波纹效果
                     */

                    .setActiveColor("#FF107FFD") //选中颜色
                    .setInActiveColor("#e9e6e6") //未选中颜色
                    .setBarBackgroundColor("#1ccbae");//导航栏背景色

            /** 添加导航按钮 */
            bottomNavigationBar
                    .addItem(new BottomNavigationItem(R.drawable.ic_home, "首页"))
                    .addItem(new BottomNavigationItem(R.drawable.ic_scan, "群组"))
                    .addItem(new BottomNavigationItem(R.drawable.ic_my, "个人设置"))
                    .setFirstSelectedPosition(lastSelectedPosition )
                    .initialise(); //initialise 一定要放在 所有设置的最后一项

            setDefaultFragment();//设置默认导航栏

        }

        /**
         * 设置默认导航栏
         */
        private void setDefaultFragment() {
//            HomePageTopFragment homePageTopFragment = new HomePageTopFragment();
//            HomePageCenterFragment homePageCenterFragment = new HomePageCenterFragment();
//            HomePageBottomFragment homePageBottomFragment = new HomePageBottomFragment();
            mHomeFragment = HomeFragment.newInstance("首页");
            replaceFragment(mHomeFragment);
        }

        private void replaceFragment(Fragment fragment){
            android.support.v4.app.FragmentManager fragmentManager = getSupportFragmentManager();
            android.support.v4.app.FragmentTransaction transaction = fragmentManager.beginTransaction();
            transaction.replace(R.id.tb,fragment);
            transaction.commit();
        }

        /**
         * 设置导航选中的事件
         */
        @Override
        public void onTabSelected(int position) {
            Log.d(TAG, "onTabSelected() called with: " + "position = [" + position + "]");
            switch (position) {
                case 0:
                    if (mHomeFragment == null) {
                        mHomeFragment = HomeFragment.newInstance("首页");
                    }
                    replaceFragment(mHomeFragment);
                    break;
                case 1:
                    if (mScanFragment == null) {
                        mScanFragment = ScanFragment.newInstance("扫一扫");
                    }
                    replaceFragment(mScanFragment);
                    break;
                case 2:
                    if (mMyFragment == null) {
                        mMyFragment = MyFragment.newInstance("个人中心");
                    }
                    replaceFragment(mMyFragment);
                    break;

                default:
                    break;
            }
        }

        /**
         * 设置未选中Fragment 事务
         */
        @Override
        public void onTabUnselected(int position) {

        }

        /**
         * 设置释放Fragment 事务
         */
        @Override
        public void onTabReselected(int position) {

        }
    }



