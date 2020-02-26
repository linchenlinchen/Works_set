package com.free.diary.model.dao.base;

import java.util.List;


public interface IDao<T> {

    public void insert(T t);

    public void insert(List<T> list);

    public void update(T t);

    public List<T> queryAll();

    public List<T> query(int pageNum, int pageSize);

    public void delete(T t);

    public void delelteAll();
}
