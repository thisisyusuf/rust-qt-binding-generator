/* generated by rust_qt_binding_generator */
#include "Tree.h"

namespace {
    struct qbytearray_t {
    private:
        const char* data;
        int len;
    public:
        qbytearray_t(const QByteArray& v):
            data(v.data()),
            len(v.size()) {
        }
        operator QByteArray() const {
            return QByteArray(data, len);
        }
    };
    struct qstring_t {
    private:
        const void* data;
        int len;
    public:
        qstring_t(const QString& v):
            data(static_cast<const void*>(v.utf16())),
            len(v.size()) {
        }
        operator QString() const {
            return QString::fromUtf8(static_cast<const char*>(data), len);
        }
    };
    struct qmodelindex_t {
        int row;
        quintptr id;
    };
}
typedef void (*qstring_set)(QString*, qstring_t*);
void set_qstring(QString* v, qstring_t* val) {
    *v = *val;
}
typedef void (*qbytearray_set)(QByteArray*, qbytearray_t*);
void set_qbytearray(QByteArray* v, qbytearray_t* val) {
    *v = *val;
}

extern "C" {
    TreeInterface* tree_new(Tree*, void (*)(Tree*),
        void (*)(Tree*, int, quintptr, int, int),
        void (*)(Tree*),
        void (*)(Tree*, int, quintptr, int, int),
        void (*)(Tree*));
    void tree_free(TreeInterface*);
    void tree_path_get(TreeInterface*, QString*, qstring_set);
    void tree_path_set(void*, qstring_t);
};
Tree::Tree(QObject *parent):
    QAbstractItemModel(parent),
    d(tree_new(this,
        [](Tree* o) { emit o->pathChanged(); },
        [](Tree* o, int row, quintptr id, int first, int last) {
            emit o->beginInsertRows(o->createIndex(row, 0, id), first, last);
        },
        [](Tree* o) {
            emit o->endInsertRows();
        },
        [](Tree* o, int row, quintptr id, int first, int last) {
            emit o->beginRemoveRows(o->createIndex(row, 0, id), first, last);
        },
        [](Tree* o) {
            emit o->endRemoveRows();
        }
)) {}

Tree::~Tree() {
    tree_free(d);
}
QString Tree::path() const
{
    QString v;
    tree_path_get(d, &v, set_qstring);
    return v;
}
void Tree::setPath(const QString& v) {
    tree_path_set(d, v);
}
extern "C" {
    void tree_data_file_name(const TreeInterface*, int, quintptr, QString*, qstring_set);
    void tree_data_file_icon(const TreeInterface*, int, quintptr, QByteArray*, qbytearray_set);
    void tree_data_file_path(const TreeInterface*, int, quintptr, QString*, qstring_set);
    int tree_data_file_permissions(const TreeInterface*, int, quintptr);

    int tree_row_count(const TreeInterface*, int, quintptr);
    bool tree_can_fetch_more(const TreeInterface*, int, quintptr);
    void tree_fetch_more(TreeInterface*, int, quintptr);
    quintptr tree_index(const TreeInterface*, int, quintptr);
    qmodelindex_t tree_parent(const TreeInterface*, int, quintptr);
}
int Tree::columnCount(const QModelIndex &) const
{
    return 3;
}

int Tree::rowCount(const QModelIndex &parent) const
{
    return tree_row_count(d, parent.row(), parent.internalId());
}

QModelIndex Tree::index(int row, int column, const QModelIndex &parent) const
{
    const quintptr id = tree_index(d, parent.row(), parent.internalId());
    return id ?createIndex(row, column, id) :QModelIndex();
}

QModelIndex Tree::parent(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }
    const qmodelindex_t parent = tree_parent(d, index.row(), index.internalId());
    return parent.id ?createIndex(parent.row, 0, parent.id) :QModelIndex();
}

bool Tree::canFetchMore(const QModelIndex &parent) const
{
    return tree_can_fetch_more(d, parent.row(), parent.internalId());
}

void Tree::fetchMore(const QModelIndex &parent)
{
    tree_fetch_more(d, parent.row(), parent.internalId());
}

QVariant Tree::data(const QModelIndex &index, int role) const
{
    QVariant v;
    QString s;
    QByteArray b;
    switch (index.column()) {
    case 0:
        switch (role) {
        case Qt::DisplayRole:
            tree_data_file_name(d, index.row(), index.internalId(), &s, set_qstring);
            v.setValue<QString>(s);
            break;
        case Qt::DecorationRole:
            tree_data_file_icon(d, index.row(), index.internalId(), &b, set_qbytearray);
            v.setValue<QByteArray>(b);
            break;
        case Qt::UserRole + 1:
            tree_data_file_path(d, index.row(), index.internalId(), &s, set_qstring);
            v.setValue<QString>(s);
            break;
        case Qt::UserRole + 2:
            tree_data_file_name(d, index.row(), index.internalId(), &s, set_qstring);
            v.setValue<QString>(s);
            break;
        case Qt::UserRole + 3:
            v.setValue<int>(tree_data_file_permissions(d, index.row(), index.internalId()));
            break;
        }
        break;
    case 1:
        switch (role) {
        case Qt::DisplayRole:
            tree_data_file_path(d, index.row(), index.internalId(), &s, set_qstring);
            v.setValue<QString>(s);
            break;
        }
        break;
    case 2:
        switch (role) {
        case Qt::DisplayRole:
            v.setValue<int>(tree_data_file_permissions(d, index.row(), index.internalId()));
            break;
        }
        break;
    }
    return v;
}
QHash<int, QByteArray> Tree::roleNames() const {
    QHash<int, QByteArray> names;
    names.insert(Qt::DisplayRole, "FileName");
    names.insert(Qt::DecorationRole, "FileIcon");
    names.insert(Qt::UserRole + 1, "FilePath");
    names.insert(Qt::UserRole + 3, "FilePermissions");
    return names;
}

